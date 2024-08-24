//
//  darwin.cpp
//  acme_darwin
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2023-04-24 12:27
//
#include <sys/types.h>
#include <sys/sysctl.h>




//https://stackoverflow.com/questions/46070563/how-can-i-get-all-process-name-in-os-x-programmatically-not-just-app-processes
//
//
//- (NSUInteger)maxSystemProcs
//{
//    int32_t maxproc;
//    size_t len = sizeof(maxproc);
//    sysctlbyname("kern.maxproc", &maxproc, &len, NULL, 0);
//
//    return (NSUInteger)maxproc;
//}
//
//- (NSUInteger)runningUserProcs
//{
//    NSUInteger maxSystemProcs = self.maxSystemProcs;
//
//    pid_t * const pids = calloc(maxSystemProcs, sizeof(pid_t));
//    NSAssert(pids, @"Memory allocation failure.");
//
//    const int pidcount = proc_listallpids(pids, (int)(maxSystemProcs * sizeof(pid_t)));
//
//    NSUInteger userPids = 0;
//    uid_t uid = geteuid();
//    for (int *pidp = pids; *pidp; pidp++) {
//        struct proc_bsdshortinfo bsdshortinfo;
//        int writtenSize;
//
//        writtenSize = proc_pidinfo(*pidp, PROC_PIDT_SHORTBSDINFO, 0, &bsdshortinfo, sizeof(bsdshortinfo));
//
//        if (writtenSize != (int)sizeof(bsdshortinfo)) {
//            continue;
//        }
//
//        if (bsdshortinfo.pbsi_uid == uid) {
//            userPids++;
//        }
//    }
//
//    free(pids);
//    return (NSUInteger)userPids;
//}

int kern_max_proc()
{

   int maxproc;

   size_t len = sizeof(maxproc);

   sysctlbyname("kern.maxproc", &maxproc, &len, NULL, 0);

   return maxproc;
   
}

//
//- (NSUInteger)runningUserProcs
//{
//    NSUInteger maxSystemProcs = self.maxSystemProcs;
//
//    pid_t * const pids = calloc(maxSystemProcs, sizeof(pid_t));
//    NSAssert(pids, @"Memory allocation failure.");
//
//    const int pidcount = proc_listallpids(pids, (int)(maxSystemProcs * sizeof(pid_t)));
//
//    NSUInteger userPids = 0;
//    uid_t uid = geteuid();
//    for (int *pidp = pids; *pidp; pidp++) {
//        struct proc_bsdshortinfo bsdshortinfo;
//        int writtenSize;
//
//        writtenSize = proc_pidinfo(*pidp, PROC_PIDT_SHORTBSDINFO, 0, &bsdshortinfo, sizeof(bsdshortinfo));
//
//        if (writtenSize != (int)sizeof(bsdshortinfo)) {
//            continue;
//        }
//
//        if (bsdshortinfo.pbsi_uid == uid) {
//            userPids++;
//        }
//    }
//
//    free(pids);
//    return (NSUInteger)userPids;
//}


