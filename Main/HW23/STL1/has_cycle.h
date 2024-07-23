#pragma once

struct Node {
    int data;
    Node* next;
};

bool has_cycle(Node* head);
