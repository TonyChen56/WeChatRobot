#pragma once

#include <Windows.h>

/*头文件声明*/
typedef LONG NTSTATUS;
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation,              // 0        Y        N
	SystemProcessorInformation,          // 1        Y        N
	SystemPerformanceInformation,        // 2        Y        N
	SystemTimeOfDayInformation,          // 3        Y        N
	SystemNotImplemented1,               // 4        Y        N
	SystemProcessesAndThreadsInformation, // 5       Y        N
	SystemCallCounts,                    // 6        Y        N
	SystemConfigurationInformation,      // 7        Y        N
	SystemProcessorTimes,                // 8        Y        N
	SystemGlobalFlag,                    // 9        Y        Y
	SystemNotImplemented2,               // 10       Y        N
	SystemModuleInformation,             // 11       Y        N
	SystemLockInformation,               // 12       Y        N
	SystemNotImplemented3,               // 13       Y        N
	SystemNotImplemented4,               // 14       Y        N
	SystemNotImplemented5,               // 15       Y        N
	SystemHandleInformation,             // 16       Y        N
	SystemObjectInformation,             // 17       Y        N
	SystemPagefileInformation,           // 18       Y        N
	SystemInstructionEmulationCounts,    // 19       Y        N
	SystemInvalidInfoClass1,             // 20
	SystemCacheInformation,              // 21       Y        Y
	SystemPoolTagInformation,            // 22       Y        N
	SystemProcessorStatistics,           // 23       Y        N
	SystemDpcInformation,                // 24       Y        Y
	SystemNotImplemented6,               // 25       Y        N
	SystemLoadImage,                     // 26       N        Y
	SystemUnloadImage,                   // 27       N        Y
	SystemTimeAdjustment,                // 28       Y        Y
	SystemNotImplemented7,               // 29       Y        N
	SystemNotImplemented8,               // 30       Y        N
	SystemNotImplemented9,               // 31       Y        N
	SystemCrashDumpInformation,          // 32       Y        N
	SystemExceptionInformation,          // 33       Y        N
	SystemCrashDumpStateInformation,     // 34       Y        Y/N
	SystemKernelDebuggerInformation,     // 35       Y        N
	SystemContextSwitchInformation,      // 36       Y        N
	SystemRegistryQuotaInformation,      // 37       Y        Y
	SystemLoadAndCallImage,              // 38       N        Y
	SystemPrioritySeparation,            // 39       N        Y
	SystemNotImplemented10,              // 40       Y        N
	SystemNotImplemented11,              // 41       Y        N
	SystemInvalidInfoClass2,             // 42
	SystemInvalidInfoClass3,             // 43
	SystemTimeZoneInformation,           // 44       Y        N
	SystemLookasideInformation,          // 45       Y        N
	SystemSetTimeSlipEvent,              // 46       N        Y
	SystemCreateSession,                 // 47       N        Y
	SystemDeleteSession,                 // 48       N        Y
	SystemInvalidInfoClass4,             // 49
	SystemRangeStartInformation,         // 50       Y        N
	SystemVerifierInformation,           // 51       Y        Y
	SystemAddVerifier,                   // 52       N        Y
	SystemSessionProcessesInformation    // 53       Y        N
} SYSTEM_INFORMATION_CLASS;

typedef struct _CLIENT_ID
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
}CLIENT_ID,*PCLIENT_ID;

typedef struct
{
	USHORT Length;
	USHORT MaxLen;
	USHORT *Buffer;
}UNICODE_STRING, *PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES 
{
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;
	PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES; 

typedef struct _IO_COUNTERSEX {
	LARGE_INTEGER ReadOperationCount;
	LARGE_INTEGER WriteOperationCount;
	LARGE_INTEGER OtherOperationCount;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
} IO_COUNTERSEX, *PIO_COUNTERSEX;

typedef enum {
	StateInitialized,
	StateReady,
	StateRunning,
	StateStandby,
	StateTerminated,
	StateWait,
	StateTransition,
	StateUnknown
} THREAD_STATE;

typedef struct _VM_COUNTERS {
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
} VM_COUNTERS;
typedef VM_COUNTERS *PVM_COUNTERS;

typedef struct _SYSTEM_THREADS {
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	PVOID StartAddress;
	CLIENT_ID ClientId;
	ULONG Priority;
	ULONG BasePriority;
	ULONG ContextSwitchCount;
	THREAD_STATE State;
	ULONG WaitReason;
} SYSTEM_THREADS, *PSYSTEM_THREADS;

typedef struct _SYSTEM_PROCESSES { // Information Class 5
	ULONG NextEntryDelta;
	ULONG ThreadCount;
	ULONG Reserved1[6];
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ProcessName;
	ULONG BasePriority;
	ULONG ProcessId;
	ULONG InheritedFromProcessId;
	ULONG HandleCount;
	ULONG Reserved2[2];
	VM_COUNTERS VmCounters;
	IO_COUNTERSEX IoCounters;  // Windows 2000 only
	SYSTEM_THREADS Threads[1];
} SYSTEM_PROCESSES, *PSYSTEM_PROCESSES;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG            ProcessId;
	UCHAR            ObjectTypeNumber;
	UCHAR            Flags;
	USHORT            Handle;
	PVOID            Object;
	ACCESS_MASK        GrantedAccess;
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO {
	USHORT UniqueProcessId;
	USHORT CreatorBackTraceIndex;
	UCHAR ObjectTypeIndex;
	UCHAR HandleAttributes;
	USHORT HandleValue;
	PVOID Object;
	ULONG GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION1 {
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[ 1 ];
} SYSTEM_HANDLE_INFORMATION1, *PSYSTEM_HANDLE_INFORMATION1;

typedef enum _OBJECT_INFORMATION_CLASS {
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectAllInformation,
	ObjectDataInformation
} OBJECT_INFORMATION_CLASS;

typedef struct _OBJECT_NAME_INFORMATION {
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;



void OpenWeChat();
int PatchWeChat();
BOOL IsTargetPid(DWORD Pid, DWORD* Pids, int num);
int GetProcIds(LPWSTR Name, DWORD* Pids);
HANDLE DuplicateHandleEx(DWORD pid, HANDLE h, DWORD flags);
BOOL ElevatePrivileges();