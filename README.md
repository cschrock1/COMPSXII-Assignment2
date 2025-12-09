# Memory Manager Assignment

## Overview
This assignment builds a dynamic game inventory system to practice manual memory management in C. You'll use malloc, calloc, realloc, and free to control memory explicitly, experience memory leaks and dangling pointers, then systematically fix these errors.

## Files in This Repository
- `memory_manager.c` - Main assignment file with TODO sections to complete
- `compile_and_run.sh` - Helper script to compile and run your program
- `README.md` - This file

## What You Need to Do

Complete all TODO sections in `memory_manager.c`:

1. **Part 1: Create Inventory** - Use malloc to allocate arrays for item IDs and quantities
2. **Part 2: Expand Inventory** - Use realloc to dynamically grow inventory size
3. **Part 3: Fix Memory Leaks** - Add missing free() calls to prevent leaks
4. **Part 4: Safe Pointer Handling** - Set pointers to NULL after freeing and check before use

## Compiling Your Program

```bash
gcc -Wall -Wextra memory_manager.c -o memory_manager
./memory_manager
```

### For Windows Users
```bash
gcc -Wall -Wextra memory_manager.c -o memory_manager.exe
memory_manager.exe
```

### Memory Leaks
A memory leak occurs when you allocate memory but never free it. The leaked memory remains unavailable until your program ends. In long-running applications, leaks accumulate and eventually consume all available memory.

**Example of a leak:**
```c
void bad_function() {
    int *data = (int*)malloc(100 * sizeof(int));
    // Use data...
    // Missing free(data) - memory is leaked!
}
```

**Fixed version:**
```c
void good_function() {
    int *data = (int*)malloc(100 * sizeof(int));
    if (data != NULL) {
        // Use data...
        free(data);  // Properly freed
    }
}
```

### Dangling Pointers
A dangling pointer points to memory that has been freed. Using a dangling pointer causes undefined behavior (crashes, garbage data, or appearing to work).

**Example of dangling pointer:**
```c
int *ptr = (int*)malloc(sizeof(int));
*ptr = 42;
free(ptr);
printf("%d\n", *ptr);  // Dangling pointer access - undefined behavior!
```

**Safe version:**
```c
int *ptr = (int*)malloc(sizeof(int));
*ptr = 42;
free(ptr);
ptr = NULL;  // Set to NULL after freeing

if (ptr != NULL) {
    printf("%d\n", *ptr);  // Won't execute
} else {
    printf("Pointer is NULL\n");  // Safe path
}
```

## Debugging Memory Issues

### Detecting Memory Leaks
Without special tools, memory leaks are invisible. Your program appears to work correctly but uses more memory than necessary. In this assignment, Part 3 demonstrates a leak by allocating in a loop without freeing.

### Common Errors and Solutions

**Error**: Segmentation fault when running program
- **Cause**: Accessing freed memory (dangling pointer) or dereferencing NULL
- **Solution**: Check pointers for NULL before use, set to NULL after free

**Error**: Program crashes on exit or in seemingly unrelated places
- **Cause**: Double free (freeing the same memory twice)
- **Solution**: Set pointer to NULL immediately after free

**Error**: Program gradually uses more memory over time
- **Cause**: Memory leak (missing free() call)
- **Solution**: Ensure every malloc/calloc/realloc has a matching free

## Common Mistakes to Avoid

1. **Forgetting to check if malloc succeeded**
   ```c
   int *ptr = (int*)malloc(sizeof(int));
   *ptr = 42;  // WRONG - what if malloc returned NULL?
   ```

2. **Freeing stack variables**
   ```c
   int x = 10;
   free(&x);  // WRONG - can only free heap-allocated memory
   ```

3. **Using freed memory**
   ```c
   int *ptr = (int*)malloc(sizeof(int));
   free(ptr);
   *ptr = 42;  // WRONG - dangling pointer
   ```

4. **Losing the pointer before freeing**
   ```c
   int *ptr = (int*)malloc(100 * sizeof(int));
   ptr = NULL;  // WRONG - now we can't free it, memory leaked
   ```

## Reflection Questions

Your written reflection should address:

1. **Memory Leak Observations**: What code caused the leak in Part 3? What happens if this runs repeatedly?

2. **Python vs C**: What manual tasks did you perform that Python handles automatically?

3. **Garbage Collection Trade-offs**: Why does Python's automatic approach have performance costs? Why choose manual management despite the risks?

## Submission Requirements

1. **Code**: Push your completed `memory_manager.c` to GitHub
2. **Reflection**: Include `reflection.txt` or `reflection.md` (500-600 words)

Good luck managing memory manually!