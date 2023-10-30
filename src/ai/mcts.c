#include "generate_moves.h"
#include "struct.h"
#include "global.h"
#include "define.h"
#include "utils.h"
#include "move.h"
#include "test.h"
#include "ai.h"

node_t* createnode_t() {
    node_t* newnode_t = (node_t*)malloc(sizeof(node_t));
    newnode_t->parent = NULL;
    newnode_t->children = NULL;
    newnode_t->num_children = 0;
    newnode_t->visits = 0;
    newnode_t->value = 0.0;
    newnode_t->board = get_recursive_params();
    newnode_t->is_white = !recursive_params_glo.actual_white_turn;
    return newnode_t;
}

const int move_limit = 100;

double get_node_win_rate(double value, double visits) {
    if (visits == 0) return 0;
    return ((value + visits) / 2 / visits);
}

double calculateUTC(node_t* node, int parentVisits) {
    if (node == NULL) {
        printf("node given in clculateUTC is NULL\n");
        exit(0);
    }

    if (node->visits == 0) {
        // If the node has not been visited, return a high UTC value to encourage exploration
        return INFINITY;
    }

    // Calculate the UTC value using the UCB formula
    double exploration = UCT_CONST * sqrt(log(parentVisits) / node->visits);
    double exploitation = get_node_win_rate(node->value, node->visits);

    return exploitation + exploration;
}

// Function to select the best child node using UCT (Upper Confidence Bound for Trees)
node_t* selectChild(node_t* parent) {
    if (parent == NULL) {
        printf("Parent given in selectChild is NULL\n");
        exit(0);
    }

    node_t* bestChild = NULL;
    double bestUCT = -1;

    for (int i = 0; i < parent->num_children; i++) {
        node_t* child = &(parent->children[i]);
        double UCT = calculateUTC(child, parent->visits);

        if (UCT > bestUCT) {
            bestUCT = UCT;
            bestChild = child;
        }
    }

    printf("Choice: %f / %d\n", get_node_win_rate(bestChild->value, bestChild->visits) * bestChild->visits, bestChild->visits);
    return bestChild;
}

// Function to expand a node by adding a new child
node_t* Selection(node_t* parent) {
    if (parent == NULL) {
        printf("Parent given in selection is NULL\n");
        exit(0);
    }
    if (parent->num_children == 0) return parent;
    return Selection(selectChild(parent));
}

void Expansion(node_t *parent) {
    if (parent == NULL) {
        printf("Parent given in expension is NULL\n");
        exit(0);
    }

    recursive_params_t *moves_lists = get_all_moves(parent->board);

    if (moves_lists == NULL || global_nbr_moves == 0) {
        return;
    }

    parent->num_children = global_nbr_moves;
    parent->children = malloc((global_nbr_moves + 1) * sizeof(node_t));
    if (parent->children == NULL) {
        printf("Expansion malloc failed");
        exit(0);
    }

    for (int i = 0; i < global_nbr_moves; i++) {
        parent->children[i].board = prepare_recursive_params(moves_lists[i]);
        parent->children[i].children = NULL;
        parent->children[i].parent = parent;
        parent->children[i].num_children = 0;
        parent->children[i].value = 0;
        parent->children[i].visits = 0;
        parent->children[i].is_white = !parent->is_white;
    }

    free(moves_lists);
}

// Function to simulate a random playout and return the result
double Simulation(recursive_params_t recursive_params) {
    int number_of_moves = 0;
    while (true) {
        if (!(recursive_params.local_bitboard_king & recursive_params.local_bitboard_white)) return -1;
        if (!(recursive_params.local_bitboard_king & recursive_params.local_bitboard_black)) return 1;

        if (number_of_moves > move_limit) return 0;

        recursive_params_t *moves_lists = get_all_moves(recursive_params);

        if (moves_lists == NULL) {
            printf("Move list null in Simulation");
            exit(0);
        }

        recursive_params = prepare_recursive_params(moves_lists[random_number(0, global_nbr_moves - 1)]);

        free(moves_lists);

        number_of_moves++;
    }

    return 0;
}

// Function to backpropagate the result of a simulation up the tree
void backpropagate(node_t* node, double result) {
    double temp_result = result;

    while (node != NULL) {
        if (!node->is_white) temp_result = result * -1;
        else temp_result = result;

        node->visits++;
        node->value += temp_result;
        node = node->parent;
    }
}

void printTree(node_t* root) {
    for (int i = 0; i < root->num_children; i++) {
        printf("{%d, %d}  -  ", (int)((root->children[i].value + root->children[i].visits) / 2), (int)(root->children[i].visits));
    }
    printf("\n\n\n");
}

// MCTS main loop
node_t* mcts(node_t* root) {
    for (int i = 0; i < SIMULATIONS; i++) {
        double result = 0.0;
        node_t* leaf = Selection(root);
        Expansion(leaf);
        if (leaf->children == NULL) {
            if (leaf->is_white) result = 1;
            else result = -1;
        }
        else result = Simulation(leaf->children[random_number(0, leaf->num_children - 1)].board);
        backpropagate(leaf, result);
        printf("\n\n\n\n\n");
    }

    // Return the best child of the root node based on visit counts
    node_t* bestChild = &root->children[0];
    int bestVisits = -1;
    for (int i = 0; i < root->num_children; i++) {
        node_t* child = &root->children[i];
        // printf("%f%% Win Rate   -   %f%% Certainety\n\n", (0.5 + (child->value / (double)(child->visits * 2))) * 100 ,((double)child->visits / SIMULATIONS) * 100);
        if (child->visits > bestVisits && child->visits < SIMULATIONS) {
            bestVisits = child->visits;
            bestChild = child;
        }
    }

    return bestChild;
}

// Function to free a tree of nodes
void freeTree(node_t* root) {
    if (root == NULL) {
        return; // Base case: The tree is empty
    }

    // Recursively free the children first
    for (int i = 0; i < root->num_children; i++) {
        freeTree(&root->children[i]);
    }

    // Free the current node
    if (root->num_children)
        free(root->children);
}

recursive_params_t nerd()
{
    node_t* root = createnode_t();

    // Run MCTS
    node_t* bestChild = mcts(root);
    if (bestChild == NULL) printf("NSM!\n");

    // printf("Best Child - Win Rate: %f%%, Certainety: %f%%\n\n", (0.5 + (bestChild->value / (double)(bestChild->visits * 2))) * 100, ((double)bestChild->visits / SIMULATIONS) * 100);

    recursive_params_t bestMove = bestChild->board;

    freeTree(root);
    // Don't forget to free the memory when you're done with the tree
    // free(root->children);
    free(root);

    return bestMove;
}