/*
 * Memory Manager Assignment
 * Computer Science XII - Computer Systems
 * 
 * This program implements a dynamic game inventory system to practice
 * manual memory management using malloc, calloc, realloc, and free.
 * 
 * You'll experience memory leaks and dangling pointers firsthand,
 * then systematically fix each error.
 */

#include <stdio.h>
#include <stdlib.h>

// =============================================================================
// PART 1: CREATE INVENTORY
// =============================================================================
// Build a basic inventory system that stores item IDs and quantities.
// Use malloc to allocate memory for arrays that will hold this data.

void create_inventory() {
    printf("\n=== PART 1: CREATE INVENTORY ===\n");
    
    int inventory_size = 5;
    int *item_ids = NULL;
    int *quantities = NULL;
    
    // TODO: Allocate memory for item_ids array (5 integers)
    item_ids = (int*)malloc(inventory_size * sizeof(int));
    
    // TODO: Check if malloc succeeded by comparing item_ids to NULL
    // If allocation failed, print "Failed to allocate item_ids" and return
    if (item_ids == NULL) {
        printf("Failed to allocate item_ids\n");
        return;
    }
    
    
    // TODO: Allocate memory for quantities array (5 integers)
    quantities = (int*)malloc(inventory_size * sizeof(int));
    
    // TODO: Check if malloc succeeded for quantities
    // If allocation failed, print "Failed to allocate quantities" and return
    if (quantities == NULL) {
        printf("Failed to allocate quantities\n");
        free(item_ids);
        return;
    }
    
    // Fill the inventory with starting items
    printf("Starting inventory:\n");
    for (int i = 0; i < inventory_size; i++) {
        item_ids[i] = 100 + i;      // Item IDs: 100, 101, 102, 103, 104
        quantities[i] = (i + 1) * 10; // Quantities: 10, 20, 30, 40, 50
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }
    
    // TODO: Free the allocated memory for item_ids
    free(item_ids);
    
    // TODO: Free the allocated memory for quantities
    free(quantities);
    
    printf("Memory freed successfully.\n");
}

// =============================================================================
// PART 2: EXPAND INVENTORY
// =============================================================================
// Demonstrate dynamic growth using realloc when the player acquires more items
// than the initial inventory can hold.

void expand_inventory() {
    printf("\n=== PART 2: EXPAND INVENTORY ===\n");
    
    int initial_size = 3;
    int expanded_size = 6;
    int *item_ids = NULL;
    int *quantities = NULL;
    
    // TODO: Allocate memory for item_ids array (3 integers)
    item_ids = (int*)malloc(initial_size * sizeof(int));
    
    // TODO: Check if malloc succeeded
    // If allocation failed, print "Failed to allocate item_ids" and return
    if (item_ids == NULL) {
        printf("Failed to allocate item_ids\n");
        return;
    }
    
    
    // TODO: Allocate memory for quantities array (3 integers)
    quantities = (int*)malloc(initial_size * sizeof(int));
    
    // TODO: Check if malloc succeeded for quantities
    // If allocation failed, print "Failed to allocate quantities" and return
    if (quantities == NULL) {
        printf("Failed to allocate quantities\n");
        free(item_ids);
        return;
    }
    
    // Fill initial inventory
    printf("Initial inventory (size %d):\n", initial_size);
    for (int i = 0; i < initial_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }
    
    printf("\nPlayer acquires more items! Expanding inventory...\n");
    
    // TODO: Use realloc to expand item_ids from 3 to 6 integers
    // Store the result back in item_ids    
    item_ids = (int*)realloc(item_ids, expanded_size * sizeof(int));
    // TODO: Check if realloc succeeded
    if (item_ids == NULL) {
        printf("Failed to reallocate item_ids\n");
        return;
    }

    // TODO: Use realloc to expand quantities from 3 to 6 integers
    quantities = (int*)realloc(quantities, expanded_size * sizeof(int));
    // TODO: Check if realloc succeeded
    if (quantities == NULL) {
        printf("Failed to reallocate quantities\n");
        free(item_ids);
        return;
    }

    // Add new items to expanded inventory
    for (int i = initial_size; i < expanded_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);
    }
    
    // Print full expanded inventory
    printf("Expanded inventory (size %d):\n", expanded_size);
    for (int i = 0; i < expanded_size; i++) {
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }
    
    // TODO: Free the allocated memory for item_ids
    free(item_ids);
    
    // TODO: Free the allocated memory for quantities
    free(quantities);
    
    printf("Memory freed successfully.\n");
}

// =============================================================================
// PART 3: MEMORY LEAK DEMONSTRATION
// =============================================================================
// This function demonstrates a memory leak by allocating memory without freeing it.
// Run this version first to see what happens when memory is never freed.

void memory_leak_demo() {
    printf("\n=== PART 3A: MEMORY LEAK DEMONSTRATION ===\n");
    printf("Allocating memory in a loop WITHOUT freeing...\n");
    
    for (int i = 0; i < 1000; i++) {
        // Allocate memory for a temporary item
        int *temp_item = (int*)malloc(1000 * sizeof(int));
        
        if (temp_item == NULL) {
            printf("Allocation failed at iteration %d!\n", i);
            return;
        }
        
        // Use the memory
        temp_item[0] = 300 + i;
        
        // NO FREE - Memory is leaked!
        // Each iteration leaks 4000 bytes (1000 ints * 4 bytes each)
    }
    
    printf("Loop complete. Leaked approximately %zu KB of memory.\n", 
           (1000 * 1000 * sizeof(int)) / 1024);
    printf("This memory cannot be reused until the program ends.\n");
}

// =============================================================================
// PART 3B: FIXED VERSION - NO MEMORY LEAK
// =============================================================================
// This function properly frees memory after each allocation.
// Compare the behavior of this version to the leaking version above.

void memory_leak_fixed() {
    printf("\n=== PART 3B: FIXED VERSION - NO MEMORY LEAK ===\n");
    printf("Allocating memory in a loop WITH proper freeing...\n");
    
    for (int i = 0; i < 1000; i++) {
        // Allocate memory for a temporary item
        int *temp_item = (int*)malloc(1000 * sizeof(int));
        
        if (temp_item == NULL) {
            printf("Allocation failed at iteration %d!\n", i);
            return;
        }
        
        // Use the memory
        temp_item[0] = 300 + i;
        
        // TODO: Free the memory to prevent the leak
        free(temp_item);
        
    }
    
    printf("Loop complete. Memory properly freed after each use.\n");
    printf("Total memory allocated and freed: %zu KB\n", 
           (1000 * 1000 * sizeof(int)) / 1024);
}

// =============================================================================
// PART 4: SAFE POINTER HANDLING
// =============================================================================
// This function demonstrates dangling pointer issues and how to handle
// pointers safely after freeing memory.

void safe_pointer_handling() {
    printf("\n=== PART 4: SAFE POINTER HANDLING ===\n");
    
    // Allocate memory for player health
    int *player_health = (int*)malloc(sizeof(int));
    
    if (player_health == NULL) {
        printf("Allocation failed!\n");
        return;
    }
    
    *player_health = 100;
    printf("Player health: %d\n", *player_health);
    
    // Free the memory
    free(player_health);
    printf("Health memory freed.\n");
    
    // TODO: Set player_health to NULL after freeing to avoid dangling pointer
    // This prevents accidentally using the freed memory
    player_health = NULL;
    
    // TODO: Before using player_health, check if it's NULL
    // If it's not NULL, print the value. If it is NULL, print "Health data not available"
    // Hint: Use an if statement to check: if (player_health != NULL)
    if (player_health != NULL) {
        printf("Player health: %d\n", *player_health);
    } else {
        printf("Health data not available\n");
    }
    
    printf("Safe pointer handling complete.\n");
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {
    printf("=============================================================\n");
    printf("      MEMORY MANAGER: Dynamic Inventory System\n");
    printf("=============================================================\n");
    
    // Part 1: Basic memory allocation with malloc
    create_inventory();
    
    // Part 2: Dynamic growth with realloc
    expand_inventory();
    
    // Part 3: Memory leak demonstration and fix
    printf("\n--- First, observe the memory leak ---\n");
    memory_leak_demo();
    
    printf("\n--- Now, see the properly managed version ---\n");
    memory_leak_fixed();
    
    // Part 4: Handle pointers safely after freeing
    safe_pointer_handling();
    
    printf("\n=============================================================\n");
    printf("Memory management complete!\n");
    printf("Review your code for proper malloc/free pairing and NULL checks.\n");
    printf("=============================================================\n");
    
    return 0;
}