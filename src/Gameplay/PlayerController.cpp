#include "../Core/Input.h"
#include "../Core/Scene.h"
#include "../Core/Math.h"
#include "../Components/Components.h"
#include "../Core/Application.h"
#include "PlayerController.h"

static Transform* trans;
static DynamicBox* dynamicBox;
static Sprite* sprite;
static AnimationController* animController;

static glm::vec3 velocity;
static const glm::vec3 startPos = glm::vec3(-3.5f, -1.6f, 1.0f);
static bool spriteFlipped = false;

const static float groundAcc = 90.0f;
const static float airAcc = 15.0f;
const static float maxSpeed = 3.0f;
const static float groundFriction = 35.0f;
const static float airFriction = 5.0f;

const static int idleState = 0;
const static int runState = 1;
const static int jumpState = 2;
const static int fallState = 3;

void PlayerStart() {
    entt::entity playerEntity = CreateEntity(startPos);
    trans = &GetComponent<Transform>(playerEntity);

    dynamicBox = &AddComponent<DynamicBox>(playerEntity);
    dynamicBox->Init(0.15f, 0.3f, trans->position);

    auto& dynamicCircle = AddComponent<DynamicCircle>(playerEntity);
    dynamicCircle.radius = 0.12f;
    
    sprite = &AddComponent<Sprite>(playerEntity);
    sprite->SetTexture(Texture::GetTexture("src/Assets/Sprites/PlayerIdle.png"));
    sprite->SubTexture(Texture::GetTexture("src/Assets/Sprites/PlayerIdle.png"), glm::vec2(16, 80), 32, 32);

    animController = &AddComponent<AnimationController>(playerEntity);
    Animation idleAnim(Texture::GetTexture("src/Assets/Sprites/PlayerIdle.png"), 10.0f, 32, 32, 9, 0);
    animController->animations.push_back(idleAnim);

    Animation runAnim(Texture::GetTexture("src/Assets/Sprites/PlayerRun.png"), 20.0f, 32, 32, 6, 0);
    animController->animations.push_back(runAnim);

    Animation jumpAnim(Texture::GetTexture("src/Assets/Sprites/PlayerJump.png"), 10.0f, 32, 32, 4, 1);
    animController->animations.push_back(jumpAnim);

    Animation fallAnim(Texture::GetTexture("src/Assets/Sprites/PlayerJump.png"), 10.0f, 32, 32, 1, 5);
    animController->animations.push_back(fallAnim);
}

void PlayerUpdate(const float deltaTime) {
    float acc = (dynamicBox->downColliding) ? groundAcc : airAcc;

    if (OnKeyHold(GLFW_KEY_A)) {
        velocity.x -= acc * deltaTime;
        sprite->Flip(true);
    }
    if (OnKeyHold(GLFW_KEY_D)) {
        velocity.x += acc * deltaTime;
        sprite->Flip(false);
    }

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

    if (velocity.y > 0.0f) {
        animController->state = jumpState;
    } 
    else if (velocity.y < 0.0f && !dynamicBox->downColliding) {
        animController->state = fallState;
    }
    else if (velocity.x != 0.0f) {
        animController->state = runState;
    }
    else {
        animController->state = idleState;
    }

    if (OnKeyHold(GLFW_KEY_SPACE) && dynamicBox->downColliding) {
        velocity.y = 4.0f;
    }
    else {
        velocity.y -= 10.0f * deltaTime;
        if (dynamicBox->downColliding) {
            velocity.y = -2.0f;
        }
    }

    trans->position += velocity * deltaTime;
}

void OnSawTrigger() {
    velocity = glm::vec3(0, 0, 0);
    trans->position = startPos;
    dynamicBox->lastCenter = startPos;
    dynamicBox->center = startPos;
}
