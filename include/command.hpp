#pragma once
#include <string>

struct Command {
    virtual ~Command() = default;
    virtual void run() const = 0;
};

struct FilterCommand : Command {
    std::string input, output, filter;
    FilterCommand(std::string in, std::string out, std::string filtr)
        : input(in), output(out), filter(filtr) {}
    void run() const override;
};

struct ListCommand : Command {
    void run() const override;
};