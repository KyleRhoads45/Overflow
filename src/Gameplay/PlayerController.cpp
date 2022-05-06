#include "../Core/Input.h"
#include "../Core/Scene.h"
#include "../Core/Math.h"
#include "../Components/Components.h"
#include "../Core/Application.h"
#include "PlayerController.h"
#include <iostream>

static Transform* trans;
static DynamicBox* dynamicBox;
static Sprite* sprite;
static AnimationController* animController;

static glm::vec3 velocity;
static bool spriteFlipped = false;

const static float groundAcc = 90.0f;
const static float airAcc = 15.0f;
const static float maxSpeed = 3.0f;
const static float groundFriction = 35.0f;
const static float airFriction = 3.5f;

static bool jumping = false;
const static float minJumpForce = 0.3f;
const static float jumpAcc = 27.0f;
const static float maxJumpForce = 4.0f;

const static int idleState = 0;
const static int runState = 1;
const static int jumpState = 2;
const static int fallState = 3;

static void Move(const float deltaTime);
static void ClampMovement(const float deltaTime);
static void UpdateAnimations();
static void ApplyGravity(const float deltaTime);

void PlayerUpdate(const float deltaTime) {
	const auto& playerView = GetComponentView<DynamicBox>();
	if (playerView.size() == 0) return;

	trans = &GetComponent<Transform>(playerView[0]);
	dynamicBox = &GetComponent<DynamicBox>(playerView[0]);
    sprite = &GetComponent<Sprite>(playerView[0]);
    animController = &GetComponent<AnimationController>(playerView[0]);

    Move(deltaTime);
    ClampMovement(deltaTime);
    ApplyGravity(deltaTime);
    UpdateAnimations();

    trans->position += velocity * deltaTime;
}

void OnSawTrigger() {
    LoadScene(activeScene.name);
}

static void Move(const float deltaTime) {
    float acc = (dynamicBox->downColliding) ? groundAcc : airAcc;

    if (OnKeyHold(GLFW_KEY_A)) {
        velocity.x -= acc * deltaTime;
        sprite->Flip(true);
    }
    if (OnKeyHold(GLFW_KEY_D)) {
        velocity.x += acc * deltaTime;
        sprite->Flip(false);
    }
}

static void ClampMovement(const float deltaTime) {
    if (glm::abs(velocity.x) > maxSpeed) {
        velocity.x = maxSpeed * glm::sign(velocity.x);
    }

    float friction = (dynamicBox->downColliding) ? groundFriction : airFriction;
    velocity.x = MoveTowardsZero(velocity.x, friction * deltaTime);

    if (dynamicBox->upColliding) {
        velocity.y = 0.0f;
    }
    if (dynamicBox->rightColliding || dynamicBox->leftColliding) {
        velocity.x = 0.0f;
    }
}

static void UpdateAnimations() {
    if (velocity.y > 0.0f) {
        animController->state = jumpState;
    } 
    else if (velocity.y < 0.0f && !dynamicBox->downColliding) {
        animController->state = fallState;
    }
    else if (glm::abs(velocity.x) > 0.5f) {
        animController->state = runState;
    }
    else {
        animController->state = idleState;
    }
}

static void ApplyGravity(const float deltaTime) {
    if (!jumping && OnKeyHold(GLFW_KEY_SPACE) && dynamicBox->downColliding) {
        jumping = true;
        velocity.y = minJumpForce;
    }

    if (OnKeyHold(GLFW_KEY_SPACE) && jumping) {
        velocity.y += jumpAcc * deltaTime;
    }

    if (!OnKeyHold(GLFW_KEY_SPACE) && jumping) {
        jumping = false;
    }

    if (velocity.y >= maxJumpForce) {
        velocity.y = maxJumpForce;
        jumping = false;
    }

    if (!jumping) {
        velocity.y -= 13.0f * deltaTime;
        if (dynamicBox->downColliding) {
            velocity.y = -2.0f;
        }
    }
}
