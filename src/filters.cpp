#include "filters.hpp"

#include <cmath>
#include <cstring>
#include <pixelwindow.hpp>

#include "image.hpp"
#include <thread>

namespace filters {
const std::map<std::string, FilterFn>& filter_table() {
    static const std::map<std::string, FilterFn> table = {
        {"negative", negative},
        {"flipv", flip_vertical},
        {"grayscale", grayscale},
        {"blur", blur},
        {"edge", edge_detect}};

    return table;
}

void negative(std::uint8_t* data, int width, int height) {
    const int channels = static_cast<int>(ChannelType::RGB);
    for (int i = 0; i < width * height * channels; i++) {
        data[i] = 255 - data[i];
    }
}

void flip_vertical(std::uint8_t* data, int width, int height) {
    const int step = width * 3;
    for (int row = 0; row < height / 2; ++row) {
        for (int col = 0; col < step; ++col) {
            auto& top = data[row * step + col];
            auto& bot = data[(height - 1 - row) * step + col];
            std::swap(top, bot);
        }
    }
}

void grayscale(std::uint8_t* data, int width, int height) {
    for (int i = 0; i < width * height * 3; i += 3) {
        // Grayscale Value = (0.299 * Red) + (0.587 * Green) + (0.114 * Blue
        auto gray = 0.299 * data[i] + 0.587 * data[i + 1] + 0.114 * data[i + 2];
        data[i] = gray;
        data[i + 1] = gray;
        data[i + 2] = gray;
    }
}

void blur_rows(int startRow, int endRow, std::uint8_t* buffer, const std::uint8_t* data, int width, int height){
    for (int y = startRow; y < endRow; y++) {
        for (int x = 0; x < width; x++) {
            PixelWindow win{data, width, height, x, y, 5};
            int r_sum = 0, g_sum = 0, b_sum = 0;
            int count = 0;
            for (int dx = -win.radius; dx <= win.radius; dx++) {
                for (int dy = -win.radius; dy <= win.radius; dy++) {
                    auto pxl = win.at(dx, dy);
                    if (pxl.has_value()) {
                        r_sum += pxl->r;
                        g_sum += pxl->g;
                        b_sum += pxl->b;
                        count++;
                    }
                }
            }
            r_sum = r_sum / count;
            g_sum = g_sum / count;
            b_sum = b_sum / count;
            int index = (y * width + x) * 3;
            buffer[index] = r_sum;
            buffer[index + 1] = g_sum;
            buffer[index + 2] = b_sum;
        }
    }
}

void blur(std::uint8_t* data, int width, int height) {
    std::vector<std::uint8_t> buffer(width * height * 3);

    int numOfThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads{};
    int rowBatch = height / numOfThreads; 
    for(int i = 0; i < numOfThreads; i++){
        int start = i * rowBatch;
        int end = (i == numOfThreads - 1) ? height : start + rowBatch;
        std::thread thread(blur_rows, start, end, buffer.data(), data, width, height);
        threads.push_back(std::move(thread));
    }
    for(auto& thread: threads){
       thread.join(); 
    }
    std::memcpy(data, buffer.data(), width * height * 3);
}

void edge_detect_rows(int startRow, int endRow, std::uint8_t* buffer, const std::uint8_t* data, int width, int height, const std::int8_t* sobelX, const std::int8_t* sobelY){
    for (int y = startRow; y < endRow; y++) {
        for (int x = 0; x < width; x++) {
            PixelWindow win{data, width, height, x, y, 1};
            int Gx = 0;
            int Gy = 0;
            for (int dx = -win.radius; dx <= win.radius; dx++) {
                for (int dy = -win.radius; dy <= win.radius; dy++) {
                    auto pxl = win.at(dx, dy);
                    if (pxl.has_value()) {
                        Gx += pxl->r * sobelX[(dy + 1) * 3 + (dx + 1)];
                        Gy += pxl->r * sobelY[(dy + 1) * 3 + (dx + 1)];
                    }
                }
            }
            int index = (y * width + x) * 3;
            int gradient =
                std::min(255, static_cast<int>(std::sqrt(Gx * Gx + Gy * Gy)));
            buffer[index] = gradient;
            buffer[index + 1] = gradient;
            buffer[index + 2] = gradient;
        }
    }
}

void edge_detect(std::uint8_t* data, int width, int height) {
    grayscale(data, width, height);

    std::vector<std::uint8_t> buffer(width * height * 3);

    std::int8_t sobelX[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    std::int8_t sobelY[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int numOfThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    int rowBatch = height / numOfThreads;
    for(int i = 0; i < numOfThreads; i++) {
        int startRow = i * rowBatch;
        int endRow = (i == numOfThreads - 1) ? height : startRow + rowBatch;
        std::thread thread(edge_detect_rows, startRow, endRow, buffer.data(), data, width, height, sobelX, sobelY);
        threads.push_back(std::move(thread));
    } 

    for(auto& thread: threads) {
        thread.join();
    }

    std::memcpy(data, buffer.data(), width * height * 3);
}
}  // namespace filters
