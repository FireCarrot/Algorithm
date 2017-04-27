#include <stdint.h>  // for intptr_t

namespace v8 {
namespace internal {

typedef uint8_t byte;
typedef byte* Address;

// Zap-value: The value used for zapping dead objects. Should be a recognizable
// illegal heap object pointer.
const Address kZapValue = reinterpret_cast<Address>(0xdeadbeed);
const Address kHandleZapValue = reinterpret_cast<Address>(0xbaddead);
const Address kFromSpaceZapValue = reinterpret_cast<Address>(0xbeefdad);

typedef bool (*WeakSlotCallback)(Object** pointer);

// NOTE: SpaceIterator depends on AllocationSpace enumeration values being
// consecutive and that NEW_SPACE is the first.
enum AllocationSpace {
  NEW_SPACE,
  OLD_SPACE,
  CODE_SPACE,
  MAP_SPACE,
  LO_SPACE,
  LAST_SPACE = LO_SPACE
};
const int kSpaceTagSize = 3;
const int kSpaceTagMask = (1 << kSpaceTagSize) - 1;

// A flag that indicates whether objects should be pretenured when
// allocated (allocated directory into the old generation) or not
// (allocated in the young generation if the object size and type
// allows).
enum PretenureFlag { NOT_TENURED, TENURED };

enum GarbageCollector { SCAVENGER, MARK_COMPACTOR };


// A CodeDesc describes a buffer holding instructions and relocation
// information. The instructions start at the beginning of the buffer
// and grow forward, the relocation information starts at the end of
// the buffer and grows backward.
//
// |<-----------buffer_size --------------->|
// |<--instr_size-->|      |<--reloc_size-->|
// +================+======+================+
// |   instructions | free |   reloc info   |
// +================+======+================+
// ^
// |
// buffer

struct CodeDesc {
  byte* buffer;
  int buffer_size;
  int instr_size;
  int reloc_size;
};


// Callback function on object slots, used for iterating heap object slots in
// HeapObjects, global pointers to heap objects, etc. The callback allows the
// callback function to change the value of the slot.
typedef void (*ObjectSlotCallback)(HeapObject** pointer);


// Callback function used for iterating objects in heap spaces,
// for example, scanning heap objects.
typedef int (*HeapObjectCallback)(HeapObject* obj);

// Callback function used for checking constraints when copying/relocating
// objects. Returns true if an object can be copied/relocated from its
// old_Addr to a new_addr.
typedef bool (*ConstraintCallback)(Address new_addr, Address old_addr);

// Callback function on inline caches, used for iterating over inline caches
// in compiled code.
typedef void (*InlineCacheCallback)(Code* code, Address ic);


//State for inline cache call sites. Aliased as IC::State.
enum InlineCacheState {
  // Has never been executed.
  UNINITIALIZED,
  // Has been executed but monomorphic state has been delayed.
  PREMONOMORPHIC,
  // Has been executed and only one receiver type has been seen.
  MONOMORPHIC,
  // Like MONOMORPHIC but check failed due to prototype.
  MONOMORPHIC_PROTOTYPE_FAILURE,
  // Multiple receiver types have been seen.
  MEGAMORPHIC,
  // Special states for debug break or step in prepare stubs.
  DEBUG_BREAK,
  DEBUG_PREPARE_STEP_IN
};


// Type of properties.
enum PropertyType {
  NORMAL                 = 0, // only in slow mode
  MAP_TRANSITION         = 1, // only in fast mode
  CONSTANT_FUNCTION      = 2, // only in fast mode
  FIELD                  = 3, // only in fast mode
  CALLBACKS              = 4,
  CONSTANT_TRANSITION    = 5, // only in fast mode
  INTERCEPTOR           = 6
};


}  // namespace internal
}  // namespace v8
