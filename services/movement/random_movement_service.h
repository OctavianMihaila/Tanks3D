#ifndef RANDOM_MOVEMENT_SERVICE_H
#define RANDOM_MOVEMENT_SERVICE_H

#include <iostream>
#include <random>
#include <map>
#include <string>

class RandomMovementService {
public:
    RandomMovementService();

    enum class MovementState {
        Stopped,
        GoingForward,
        GoingBackward,
        InPlaceRotationLeft,
        InPlaceRotationRight,
        FollowPlayerWithTurret,
    };

    MovementState GetNextMovementState(const MovementState currentState);

    RandomMovementService::MovementState GetNextStateAfterMoving(int randomChange);

    std::string GetMovementStateName(const MovementState state) const;

private:
    std::default_random_engine randomEngine;

    int GetRandomNumberInRange(const int minInclusive, const int maxInclusive) const;
};

#endif
