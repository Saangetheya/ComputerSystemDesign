
// A complex data structure a fault tolerant system that had to be, if at all possible, operative 24/7/365. It can not miss an interrupt. It can not allow buffer overflow and not change any object code in memory. It has to meet real time latency constraints, system wide, of 10 ms and it has to do everything possible to prevent data loss. The data structure looks something like this:

//     Processer number
//     Process number currently assigned to processer number
//     Pointer to table of processes
//     Hash table to available resources to a process in a table of processes
//     Maximum number of resources to give to a process
//     All of the above could not be allowed to change outside of a critical section.

struct Process
{
  // Your process related data here
};

struct Resource
{
  // Your resource related data here
};

struct Mutex
{
  // Your mutex implementation
};

struct ProcessTableEntry
{
  int processId;
  struct Process *process;
};

struct ResourceTableEntry
{
  int resourceId;
  struct Resource *resource;
};

struct System
{
  int processorNumber;
  int processNumber;
  struct ProcessTableEntry *processTable;
  struct ResourceTableEntry *resourceTable;
  int maxResourcesPerProcess;

  // Critical section lock
  struct Mutex criticalSectionLock;
};
