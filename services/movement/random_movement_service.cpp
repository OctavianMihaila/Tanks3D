#include "random_movement_service.h"
#include <cstdlib> // Include for std::rand and std::srand

RandomMovementService::RandomMovementService() {}

RandomMovementService::MovementState RandomMovementService::GetNextMovementState(const MovementState currentState) {
    int randomChange;
    MovementState nextState = currentState;

    // what i want is to be able to change from going forward or goind backward to one of the rotations or to follow the player.
    // when i'm in rotation or follow player i want to be able to go forward or backward.

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


   // switch (currentState) {
   //     case MovementState::GoingForward:
   //     case MovementState::GoingBackward:
   //         nextState = (randomChange == 1) ? MovementState::InPlaceRotationLeft : MovementState::InPlaceRotationRight;
   //         break;

   //     case MovementState::InPlaceRotationLeft:
   //     case MovementState::InPlaceRotationRight:
   //         nextState = (randomChange == 1) ? MovementState::GoingForward : MovementState::GoingBackward;
   //         break;
   //     case MovementState::FollowPlayerWithTurret:
   //         randomChange = GetRandomNumberInRange(0, 2);
   //         nextState = GetNextMovingStateAfterFollow(randomChange);
			//break;

   //     default:
   //         break;
   // }

    std::cout << "RandomMovementService: Changed state from " << GetMovementStateName(currentState) << " to " << GetMovementStateName(nextState) << "\n";

    return nextState;
}

RandomMovementService::MovementState RandomMovementService::GetNextStateAfterMoving(int randomChange)
{
    MovementState nextState = MovementState::GoingForward;

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
    // Use std::rand and std::srand for simplicity
    return minInclusive + std::rand() % (maxInclusive - minInclusive + 1);
}
