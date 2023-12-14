#include "random_movement_service.h"
#include <cstdlib>

RandomMovementService::RandomMovementService() {}

RandomMovementService::MovementState RandomMovementService::GetNextMovementState(const MovementState currentState) {
    int randomChange;
    MovementState nextState = currentState;

    switch (currentState) {
        case MovementState::GoingForward:
        case MovementState::GoingBackward:
            randomChange = GetRandomNumberInRange(0, 2);
            nextState = GetNextStateAfterMoving(randomChange);
            break;
        case MovementState::InPlaceRotationLeft:
        case MovementState::InPlaceRotationRight:
        case MovementState::FollowPlayerWithTurret:
			randomChange = GetRandomNumberInRange(0, 1);
			nextState = (randomChange == 1) ? MovementState::GoingForward : MovementState::GoingBackward;
			break;
        default:
			break;
    }

    return nextState;
}

RandomMovementService::MovementState RandomMovementService::GetNextStateAfterMoving(int randomChange)
{
    MovementState nextState; 

    switch (randomChange) {
        case 0:
            nextState = MovementState::FollowPlayerWithTurret;
            break;
        case 1:
            nextState = MovementState::InPlaceRotationLeft;
            break;
        case 2:
            nextState = MovementState::InPlaceRotationRight;
            break;
        default:
            break;
    }

    return nextState;
}

std::string RandomMovementService::GetMovementStateName(const MovementState state) const {
    static const std::map<MovementState, std::string> kStateNames{
        { MovementState::GoingForward, "GoingForward" },
        { MovementState::GoingBackward, "GoingBackward" },
        { MovementState::InPlaceRotationLeft, "InPlaceRotationLeft" },
        { MovementState::InPlaceRotationRight, "InPlaceRotationRight" },
    };

    auto it = kStateNames.find(state);
    return (it != kStateNames.end()) ? it->second : "";
}

int RandomMovementService::GetRandomNumberInRange(const int minInclusive, const int maxInclusive) const {
    return minInclusive + std::rand() % (maxInclusive - minInclusive + 1);
}
