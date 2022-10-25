#pragma once

struct SecondDegreeEquationSolution { 
    float p1, p2; 
    int nSols;
};

SecondDegreeEquationSolution solveSecondDegreeEquation(float a, float b, float c);

