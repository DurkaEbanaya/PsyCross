#ifndef LIBAPI_H
#define LIBAPI_H

#ifndef KERNEL_H
#include "kernel.h"
#endif

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern int SetRCnt(int spec, unsigned short target, int mode);
extern int GetRCnt(int spec);
extern int ResetRCnt(int spec);
extern int StartRCnt(int spec);
extern int StopRCnt(int spec);

extern int OpenEvent(unsigned int desc, int spec, int mode, long (*func)());
extern int CloseEvent(unsigned int event);
extern int WaitEvent(unsigned int event);
extern int TestEvent(unsigned int event);
extern int EnableEvent(unsigned int event);
extern int DisableEvent(unsigned int event);
extern void DeliverEvent(unsigned int ev1, int ev2);
extern void UnDeliverEvent(unsigned int ev1, int ev2);

extern int OpenTh(int (*func)(), unsigned int, unsigned int);
extern int CloseTh(int unk00);
extern int ChangeTh(int unk00);

/* A wasm build links libc statically into the same module as this, so these
 * PSX names would bind libc's OWN internal calls too -- opendir() opening a
 * directory through the memory-card open() below. Every platform with a
 * shared libc keeps those calls inside libc and never sees the clash. Give
 * the PSX API its own spelling here; libapi.c and the game's callers both
 * include this header, so neither side changes. rename takes const to stay
 * compatible with the <stdio.h> declaration that the macro also renames.
 * Function-like so a struct member named `read` is left alone. */
#if defined(__EMSCRIPTEN__)
#define open(...) PsyX_PsxOpen(__VA_ARGS__)
#define close(...) PsyX_PsxClose(__VA_ARGS__)
#define lseek(...) PsyX_PsxLseek(__VA_ARGS__)
#define read(...) PsyX_PsxRead(__VA_ARGS__)
#define write(...) PsyX_PsxWrite(__VA_ARGS__)
#define ioctl(...) PsyX_PsxIoctl(__VA_ARGS__)
#define rename(...) PsyX_PsxRename(__VA_ARGS__)
extern int open(char* path, unsigned int flags);
extern int close(int handle);
extern int lseek(int handle, int offset, int whence);
extern int read(int handle, void* buf, int bytes);
extern int write(int handle, void* buf, int bytes);
extern int ioctl(int unk00, int unk01, int unk02);
extern int rename(const char* oldpath, const char* newpath);
#endif
	
/*
extern int open(char* unk00, unsigned int );
extern int close(int unk00);
extern int lseek(int unk00, int , int );
extern int read(int unk00, void *, int );
extern int write(int unk00, void *, int );
extern int ioctl(int unk00, int , int );
	
extern struct DIRENTRY* firstfile(char* unk00, struct DIRENTRY *);
extern struct DIRENTRY* nextfile(struct DIRENTRY* unk00);
	
extern int erase(char* unk00);
extern int undelete(char* unk00);
extern int format(char* unk00);
extern int rename(char* unk00, char *);
extern int cd(char* unk00);
*/
	
extern int LoadTest(char*  unk00, struct EXEC *);
extern int Load(char * unk00, struct EXEC *);
extern int Exec(struct EXEC * unk00, int, char **);
extern int LoadExec(char * unk00, unsigned int, unsigned int);

extern int InitPAD(char * unk00, int,char *, int);
extern int StartPAD();
extern void StopPAD();
extern void EnablePAD();
extern void DisablePAD();

extern void FlushCache();
extern void ReturnFromException();
/*
extern int EnterCriticalSection();
extern void ExitCriticalSection();
*/
extern void Exception();
extern void SwEnterCriticalSection();
extern void SwExitCriticalSection();

extern unsigned long SetSp(unsigned long newsp);
extern unsigned long GetSp();
extern unsigned long GetGp();
extern unsigned long GetCr();
extern unsigned long GetSr();
extern unsigned long GetSysSp();

extern int SetConf(unsigned int,unsigned int,unsigned int);
extern void GetConf(unsigned int*,unsigned int*,unsigned int*);

/*
extern int _get_errno(void);
extern int _get_error(int);
*/
extern void SystemError( char, int);
extern void SetMem(int);

extern int Krom2RawAdd( unsigned int);
extern int Krom2RawAdd2(unsigned short);

extern void _96_init(void);
extern void _96_remove(void);
extern void _boot(void);

extern void ChangeClearPAD(int);

/* prototypes added by shino 96/05/22 */
extern void InitCARD(int val);
extern int StartCARD();
extern int StopCARD();
extern void _bu_init();
extern int _card_info(int chan);
extern int _card_clear(int chan);
extern int _card_load(int chan);
extern int _card_auto(int val);
extern void _new_card();
extern int _card_status(int drv);
extern int _card_wait(int drv);
extern unsigned int _card_chan(void);
extern int _card_write(int chan, int block, unsigned char *buf);
extern int _card_read(int chan, int block, unsigned char *buf);
extern int _card_format(int chan);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif


#endif
