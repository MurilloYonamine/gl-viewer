#pragma once

#include "window.h"

#include <memory>

class Simulation {
    public:
        Simulation();
        ~Simulation();
        void Update();

    private:
        Window m_Window;
};