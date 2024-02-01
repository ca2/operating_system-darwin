// Created by Camilo on 2023-10-27 00:30 <3ThomasBorregaardSorensen!!
#include "configuration/config.h"
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <string.h>
#include <errno.h>

#include <sys/param.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/sysctl.h>

#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_types.h>

#include <TargetConditionals.h>
const char * arp_a(void * p, void(*callback)(void * p, unsigned int uIp, const char * status));

#if defined(APPLE_IOS)

const char * arp_a(void * p, void(*callback)(void * p, unsigned int uIp, const char * status))
{
   
   return nullptr; // A-ha!! this is first version of arp_a (returns nullptr)
   
}

#else

//#ifdef APPLE_IOS
//#include <net/ethernet.h>
//#else
#include <net/route.h>

#include <netinet/in.h>
#include <netinet/if_ether.h>
//#endif


#include <arpa/inet.h>

#include <err.h>
#include <errno.h>
#include <netdb.h>
//#include <nlist.h>
#include <paths.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <stdarg.h>




template < const int n >
void scatprintf(char * s, int buffer_size, const char * pszFormat, ...)
{
   
   char szBuffer[n];
   
   va_list arguments;

   va_start(arguments, pszFormat);

   vsnprintf(szBuffer, buffer_size, pszFormat, arguments);
   
   va_end(arguments);
   
   strcat(s, szBuffer);
   
}


/* Note: could also use malloc() and free() */
void
ether_sprint(char * s, int buffer_size, u_char * cp)
{
    snprintf(s, buffer_size, "%x:%x:%x:%x:%x:%x", cp[0], cp[1], cp[2], cp[3], cp[4], cp[5]);
}


const char * arp_a(void * p, void(*callback)(void * p, unsigned int uIp, const char * status))
{
   
   //int nflag;

   char szStatus[2048];
   int mib[6];
   size_t needed;
   //const char *host;
   char *lim, *buf, *next;
    struct rt_msghdr *rtm;
    struct sockaddr_inarp *sin;
    struct sockaddr_dl *sdl;
    extern int h_errno;
    //struct hostent *hp;
//    int found_entry = 0;

    mib[0] = CTL_NET;
    mib[1] = PF_ROUTE;
    mib[2] = 0;
    mib[3] = AF_INET;
    mib[4] = NET_RT_FLAGS;
    mib[5] = RTF_LLINFO;
    if (sysctl(mib, 6, NULL, &needed, NULL, 0) < 0)
    {
       return "route-sysctl-estimate";
    }
    if ((buf = (char *) malloc(needed)) == NULL)
       return "malloc";
    if (sysctl(mib, 6, buf, &needed, NULL, 0) < 0)
       return "actual retrieval of routing table";
    lim = buf + needed;
    for (next = buf; next < lim; next += rtm->rtm_msglen) {
        rtm = (struct rt_msghdr *)next;
        sin = (struct sockaddr_inarp *)(rtm + 1);
        sdl = (struct sockaddr_dl *)(sin + 1);
//        if (addr) {
//            if (addr != sin->sin_addr.s_addr)
//                continue;
//            found_entry = 1;
//        }
//        if (nflag == 0)
//            hp = gethostbyaddr((caddr_t)&(sin->sin_addr),
//                sizeof sin->sin_addr, AF_INET);
//        else
//            hp = 0;
//        if (hp)
//            host = hp->h_name;
//        else {
//            host = "?";
//            if (h_errno == TRY_AGAIN)
//                nflag = 1;
//        }
       
       //printf("%s (%s) at ", host, inet_ntoa(sin->sin_addr));
//       auto paddress = __create_new<::networking_bsd::address>();
//
//       paddress->set_address(*sin->sin_addr);
//
//       paddress->m_strName = host;
//
//       pitema->add(paddress);

        if (sdl->sdl_alen)
           ether_sprint(szStatus, sizeof(szStatus),  ((u_char *)LLADDR(sdl)));
        else
           snprintf(szStatus, sizeof(szStatus), "%s","(incomplete)");
        if (rtm->rtm_rmx.rmx_expire == 0)
           scatprintf<256>(szStatus, sizeof(szStatus), "%s"," permanent");
        if (sin->sin_other & SIN_PROXY)
           scatprintf<256>(szStatus, sizeof(szStatus), "%s"," published (proxy only)");
        if (rtm->rtm_addrs & RTA_NETMASK)
        {
            sin = (struct sockaddr_inarp *)
                (sdl->sdl_len + (char *)sdl);
            if (sin->sin_addr.s_addr == 0xffffffff)
               scatprintf<256>(szStatus, sizeof(szStatus), "%s", " published");
            if (sin->sin_len != 8)
               scatprintf<256>(szStatus, sizeof(szStatus), "%s", "(weird)");
        }
       callback(p, sin->sin_addr.s_addr, szStatus);
        //printf("\n");
    }
  //  return (found_entry);
//}
//       for (curr = list; curr != NULL; curr = curr->ifa_next)
//       {
//   //        if (!strcmp(name, curr->ifa_name)) {
//   //            if (->sa_family == AF_INET)
//   //                result |= IFACE_IPv4;
//   //            if (curr->ifa_addr->sa_family == AF_INET6)
//   //                result |= IFACE_IPv6;
//   //        }
//
//         auto paddress = __create_new<::networking_bsd::address>();
//
//         paddress->set_address(*curr->ifa_addr);
//
//         paddress->m_strName = curr->ifa_name;
//
//         pitema->add(paddress);
//
//      }
//
//      freeifaddrs(list);

      //::informationf(strLog);

//      for (::index iItem = 0; iItem < pitema->size(); iItem++)
//      {
//
//         auto pitem = pitema->element_at(iItem);
//
//         pitem->m_item.m_iItem = iItem;
//
//      }

                        return nullptr;

   }


#endif
