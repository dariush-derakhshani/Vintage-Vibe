// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#pragma once

class BrownianMotion
{
public:
    BrownianMotion(float min, float max, float step, float initialValue)
        : minValue(min), maxValue(max), stepSize(step), currentValue(initialValue)
    {
    }

    float getNextValue()
    {
        float direction = (float)rand() / (float)RAND_MAX;
        float step = stepSize * (direction > 0.5f ? 1.0f : -1.0f);
        currentValue += step;
        currentValue = juce::jlimit(minValue, maxValue, currentValue);
        return currentValue;
    }

private:
    float minValue;
    float maxValue;
    float stepSize;
    float currentValue;
};
