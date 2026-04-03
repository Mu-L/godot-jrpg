#pragma once

#include "tactics_pawn.hpp"
#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    //Service class for handling pawn movement in the tactics game
    class TacticsPawnMovementService : public godot::RefCounted {
        GDCLASS(TacticsPawnMovementService, godot::RefCounted);

    public:
        TacticsPawnMovementService() = default;
        ~TacticsPawnMovementService() override = default;

        //Rotates the pawn to face the given direction
        //@param pawn: The TacticsPawn to rotate
        //@param dir: The direction vector to face
        void look_at_direction(tog::TacticsPawn* tactics_pawn, godot::Vector3 dir);

        //Moves the pawn along its pathfinding stack
        //@param pawn: The TacticsPawn to move
        //@param delta: Time elapsed since the last frame
        void move_along_path(tog::TacticsPawn* tactics_pawn, float delta);

        //Initiates the pawn's movement
        //@param pawn: The TacticsPawn to start moving
        void start_movement(tog::TacticsPawn* tactics_pawn);

        //Performs the actual movement of the pawn
        //@param pawn: The TacticsPawn to move
        //@param delta: Time elapsed since the last frame
        void perform_movement(tog::TacticsPawn* tactics_pawn, float delta);

        //Calculates the velocity vector for the pawn's movement
        //@param pawn: The TacticsPawn to calculate velocity for
        //@param delta: Time elapsed since the last frame
        //@return: The calculated velocity vector
        godot::Vector3 calculate_velocity(tog::TacticsPawn* tactics_pawn, float delta);

        //Calculates the current speed of the pawn
        //@param pawn: The TacticsPawn to calculate speed for
        //@return: The calculated speed
        float calculate_speed(tog::TacticsPawn* tactics_pawn);

        //Resets the movement state of the pawn
        //@param pawn: The TacticsPawn to reset
        void reset_movement_state(tog::TacticsPawn* tactics_pawn);

        //Checks if the pawn has completed its movement and adjusts accordingly
        //@param pawn: The TacticsPawn to check
        void check_movement_completion(tog::TacticsPawn* tactics_pawn);

    protected:
        static void _bind_methods() {}

    private:

    };

}

