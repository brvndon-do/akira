#pragma once

#include "enums.h"

typedef void *(*SystemInitFunction)();
typedef void (*SystemDestroyFunction)(void *);

typedef struct System_t {
    SystemType type;
    void *instance;
    SystemInitFunction initFn;
    SystemDestroyFunction destroyFn;
} System;

typedef struct SystemNode_t {
    System system;
    struct SystemNode_t *next;
} SystemNode;

typedef struct SystemManager_t {
    SystemNode *head;
} SystemManager;

void init_manager(SystemManager *manager);
void destroy_manager(SystemManager *manager);

void register_system(SystemManager *manager, SystemType type, SystemInitFunction initFn, SystemDestroyFunction destroyFn);
void *get_system(SystemManager *manager, SystemType type);

void init_all_systems(SystemManager *manager);
void destroy_all_systems(SystemManager *manager);
