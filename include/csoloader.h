#ifndef CSOLOADER_H
#define CSOLOADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "elf_util.h"
#include "linker.h"

struct csoloader {
  char *lib_path;
  struct csoloader_elf *img;
  struct linker linker;
};

/* INFO: Load a library to memory and link it */
bool csoloader_load(struct csoloader *lib, const char *lib_path);

/* INFO: Unload the library and free all related resources */
bool csoloader_unload(struct csoloader *lib);

/* INFO: Free resources related to the library without unloading it */
bool csoloader_abandon(struct csoloader *lib);

/* INFO: Move an already-loaded library into NoHello syscall-244 hidden memory in
           place (same addresses, fully functional). Call from a privileged
           (zygote-domain) context, e.g. a DenyListed app's pre-specialize. No-op
           when hiding is unavailable; the library stays a normal mapping. */
bool csoloader_hide(struct csoloader *lib);

/* INFO: Get the address of a symbol in the loaded library */
void *csoloader_get_symbol(struct csoloader *lib, const char *symbol_name);

/* INFO: Deinitializes all internal global resources */
void csoloader_deinit(void);

/* INFO: Open a NoHello capability session (syscall 244), returning its token (0 if unavailable) */
unsigned long long csoloader_nohello_session_open(uintptr_t fw_start, uintptr_t fw_end);

/* INFO: Close a NoHello capability session opened with the token from csoloader_nohello_session_open */
bool csoloader_nohello_session_close(unsigned long long token);

#ifdef __cplusplus
}
#endif

#endif /* CSOLOADER_H */