#include <stdlib.h>

#include "system.h"

void init_manager(SystemManager *manager) {
    manager->head = NULL;
}

void destroy_manager(SystemManager *manager) {
    free(manager);
}

void register_system(SystemManager *manager, SystemType type, SystemInitFunction initFn, SystemDestroyFunction destroyFn) {
    SystemNode *node = malloc(sizeof(SystemNode));
    node->system.instance = NULL;
    node->system.type = type;
    node->system.initFn = initFn;
    node->system.destroyFn = destroyFn;

    node->next = manager->head;
    manager->head = node;
}

void *get_system(SystemManager *manager, SystemType type) {
    SystemNode *current = manager->head;

    while (current) {
        if (current->system.type == type) {
            return current->system.instance;
        }

        current = current->next;
    }

    return NULL;
}

void init_all_systems(SystemManager *manager) {
    SystemNode *current = manager->head;
    
    while (current) {
        current->system.instance = current->system.initFn();
        current = current->next;
    }
}

void destroy_all_systems(SystemManager *manager) {
    SystemNode *current = manager->head;

    while (current) {
        if (current->system.instance) {
            current->system.destroyFn(current->system.instance);
        }
        SystemNode *temp = current;
        current = current->next;
        free(temp);
    }

    manager->head = NULL;
}