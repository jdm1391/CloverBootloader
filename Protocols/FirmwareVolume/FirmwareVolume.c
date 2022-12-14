//
//  FirmwareVolume.c
//  Clover
//
//  Created by Slice on 19.10.16.
//

#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <EfiImageFormat.h>
//#include <Framework/FirmwareVolumeImageFormat.h>
#include <Protocol/FirmwareVolume.h>


EFI_HANDLE              mHandle2 = NULL;

typedef struct {
    EFI_GUID Guid;
    CHAR16 Name[32];
} GUID_LIST;

EFI_GUID gGuidListGuid            = {0x0E93C52B, 0x4B73, 0x5C32, {0x86, 0xD5, 0x69, 0x25, 0x0A, 0x0B, 0xA7, 0x23}};
EFI_GUID gArrowCursorImageGuid    = {0x1A10742F, 0xFA80, 0x4B79, {0x9D, 0xA6, 0x35, 0x70, 0x58, 0xCC, 0x39, 0x7B}};
EFI_GUID gArrowCursor2xImageGuid  = {0x133D55B5, 0x8852, 0x57AC, {0xA8, 0x42, 0xF9, 0xEE, 0xBF, 0x84, 0x0C, 0x99}};

GUID_LIST GuidList[] = {
  {
    { 0x1A10742F, 0xFA80, 0x4B79, { 0x9D, 0xA6, 0x35, 0x70, 0x58, 0xCC, 0x39, 0x7B } },
    L"ArrowCursor"
  },
  {
    { 0x63FA7900, 0x6DD2, 0x4BB3, { 0x99, 0x76, 0x87, 0x0F, 0xE2, 0x7A, 0x53, 0xC2 } },
    L"BackButtonSmall"
  },
  {
    { 0x6ECEFFFD, 0x614D, 0x452E, { 0xA8, 0x1D, 0x25, 0xE5, 0x6B, 0x0D, 0xEF, 0x98 } },
    L"BatteryState0"
  },
  {
    { 0x23D1280D, 0x43F0, 0x4713, { 0x90, 0xB2, 0x0E, 0x5E, 0x42, 0x21, 0xAF, 0x4C } },
    L"BatteryState1"
  },
  {
    { 0x53531469, 0x558E, 0x4AF1, { 0x80, 0x3A, 0xF9, 0x66, 0xF2, 0x7C, 0x57, 0x3B } },
    L"BatteryState2"
  },
  {
    { 0x3BBCB209, 0x26C8, 0x4BA9, { 0xAD, 0x25, 0xB9, 0x5B, 0x45, 0xA0, 0x4D, 0x26 } },
    L"BatteryState3"
  },
  {
    { 0xED8DCDD5, 0xD037, 0x4B1F, { 0x98, 0xDD, 0xBD, 0xFD, 0xAD, 0x4D, 0xD7, 0xDD } },
    L"BatteryState4"
  },
  {
    { 0x637E0BA6, 0xC5BB, 0x41B7, { 0xA2, 0x3B, 0x3A, 0x65, 0xCF, 0xC3, 0xE9, 0xDB } },
    L"BatteryState5"
  },
  {
    { 0x7A627E16, 0x679D, 0x4814, { 0x8F, 0x82, 0xEE, 0xAF, 0x38, 0x81, 0xF0, 0x98 } },
    L"BatteryState6"
  },
  {
    { 0xE8A59290, 0xA2AF, 0x4099, { 0xB0, 0xAF, 0x32, 0x3F, 0xF9, 0xB7, 0xAB, 0x41 } },
    L"BeginBootButton"
  },
  {
    { 0xB4339807, 0x7CAC, 0x49BA, { 0x9F, 0xB7, 0x62, 0x31, 0xC6, 0x22, 0xF2, 0x70 } },
    L"BeginStickyBootButton"
  },
  {
    { 0x728CAE6C, 0x1FFC, 0x449B, { 0x86, 0x81, 0xBB, 0x2A, 0x62, 0x1E, 0x00, 0x22 } },
    L"ContinueButtonSmall"
  },
  {
    { 0xC0512F00, 0x0181, 0x48C0, { 0x8B, 0x71, 0x90, 0x50, 0x4B, 0x8F, 0x99, 0x1E } },
    L"EfiBootNameLabel"
  },
  {
    { 0x6776572C, 0xFE56, 0x42CA, { 0x9B, 0x93, 0x3D, 0x09, 0x60, 0xE7, 0x58, 0x3A } },
    L"IconBrokenBoot"
  },
  {
    { 0x410C1D0C, 0x656F, 0x4769, { 0x8D, 0xFB, 0x90, 0xF9, 0xA0, 0x30, 0x3E, 0x9F } },
    L"IconFireWireHD"
  },
  {
    { 0x21A05FD5, 0xDB4A, 0x4CFC, { 0xB8, 0x4B, 0xEB, 0x0D, 0xBB, 0x56, 0x99, 0x34 } },
    L"IconGenericCD"
  },
  {
    { 0xD872AEFA, 0x7C5F, 0x4C66, { 0x88, 0x36, 0xAA, 0x57, 0xEF, 0xF0, 0xD9, 0xF8 } },
    L"IconGenericExternalHardDrive"
  },
  {
    { 0x809FBBFD, 0x127A, 0x4249, { 0x88, 0xBC, 0xFD, 0x0E, 0x76, 0x7F, 0x4F, 0xFD } },
    L"IconInternalHD"
  },
  {
    { 0x13ECD928, 0x87AB, 0x4460, { 0xBB, 0xE0, 0xB5, 0x20, 0xF9, 0xEB, 0x1D, 0x32 } },
    L"IconNetBoot"
  },
  {
    { 0x6F92E393, 0x03C0, 0x427B, { 0xBB, 0xEB, 0x4E, 0xF8, 0x07, 0xB5, 0x5B, 0xD8 } },
    L"IconNetworkRecovery"
  },
  {
    { 0xE6F930E0, 0xBAE5, 0x40E6, { 0x98, 0xC9, 0x4C, 0xD2, 0x29, 0x82, 0x78, 0xE7 } },
    L"IconNetworkVolume"
  },
  {
    { 0xBB1A3984, 0xD171, 0x4003, { 0x90, 0x94, 0x46, 0xAF, 0x86, 0x6B, 0x45, 0xA2 } },
    L"IconPasswordLock"
  },
  {
    { 0x5B6DAB96, 0x195D, 0x4D24, { 0x97, 0x27, 0xA7, 0xD0, 0xE9, 0x36, 0x65, 0xC6 } },
    L"IconSD"
  },
  {
    { 0xA0AAFF71, 0x35DA, 0x41EE, { 0x86, 0x3F, 0xA2, 0x4F, 0x42, 0x9E, 0x59, 0xE4 } },
    L"IconSelected"
  },
  {
    { 0x1BFC532E, 0xF48A, 0x4EBE, { 0xB2, 0xFB, 0x2B, 0x28, 0x6D, 0x70, 0xA6, 0xEB } },
    L"IconUsbHD"
  },
  {
    { 0x2F08C089, 0x2073, 0x4BD9, { 0x9E, 0x7E, 0x30, 0x8A, 0x18, 0x32, 0x7B, 0x53 } },
    L"IconWirelessSmall"
  },
  {
    { 0x7914C493, 0xF439, 0x4C6C, { 0xAB, 0x23, 0x7F, 0x72, 0x15, 0x0E, 0x72, 0xD4 } },
    L"ImageAppleLogo"
  },
  {
    { 0x8F98528C, 0xF736, 0x4A84, { 0xAA, 0xA3, 0x37, 0x6A, 0x8E, 0x43, 0xBF, 0x51 } },
    L"ImagePasswordEmpty"
  },
  {
    { 0x71F3B066, 0x936A, 0x4C84, { 0x92, 0x28, 0x23, 0x23, 0x0F, 0xD4, 0x7C, 0x79 } },
    L"ImagePasswordFill"
  },
  {
    { 0x689CDA29, 0x29A8, 0x42F6, { 0x93, 0xFC, 0x46, 0xBA, 0x5F, 0x18, 0x06, 0x51 } },
    L"ImagePasswordProceed"
  },
  {
    { 0xF2C1819D, 0x10F5, 0x4223, { 0x92, 0x36, 0x9B, 0x4E, 0xBF, 0x1B, 0x9A, 0xE7 } },
    L"Logo1394"
  },
  {
    { 0xE646C3A8, 0xC7E2, 0x4DC2, { 0xA7, 0xF2, 0xE3, 0x2A, 0x27, 0x0B, 0x0B, 0x26 } },
    L"LogoThunderbolt"
  },
  {
    { 0x224FBFE4, 0xADB6, 0x4DF2, { 0xB8, 0x35, 0x60, 0x21, 0x82, 0xAE, 0xEF, 0x20 } },
    L"Clock"
  },
  {
    { 0x022218B8, 0xFE5E, 0x4EBC, { 0xBC, 0x96, 0x74, 0x05, 0x8A, 0x4E, 0x7E, 0x83 } },
    L"ErrorGlobeBorder"
  },
  {
    { 0xAD0D149F, 0xBA67, 0x4E0B, { 0xA6, 0xA2, 0x4E, 0x88, 0x53, 0x67, 0x3E, 0xA5 } },
    L"ErrorGlobeTile"
  },
  {
    { 0x290B026F, 0x6905, 0x4612, { 0xBA, 0x0F, 0xF6, 0x35, 0xDD, 0xE3, 0x52, 0x85 } },
    L"ErrorTriangle"
  },
  {
    { 0x6E66DAE5, 0x4108, 0x40B5, { 0x89, 0xA9, 0xC6, 0x10, 0x3F, 0x06, 0x39, 0xEC } },
    L"GlobeBorder"
  },
  {
    { 0xFC788727, 0xC2D0, 0x469C, { 0xBD, 0x03, 0x5A, 0xEA, 0x03, 0x32, 0x3C, 0x67 } },
    L"GlobeMask"
  }
};

UINT8 PointerImage1x[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x08, 0x04, 0x00, 0x00, 0x00, 0x4A, 0x7E, 0xF5,
    0x73, 0x00, 0x00, 0x01, 0x29, 0x49, 0x44, 0x41, 0x54, 0x38, 0x4F, 0x8D, 0xD4, 0x3D, 0x4B, 0x03,
    0x41, 0x10, 0xC6, 0xF1, 0xFF, 0xDE, 0x8B, 0xB9, 0xBB, 0x80, 0xE2, 0x4B, 0xD4, 0x80, 0x1A, 0xD0,
    0x22, 0xE1, 0x2C, 0x44, 0xAB, 0x14, 0xE9, 0x4D, 0xAF, 0x36, 0x5A, 0xF8, 0x79, 0x34, 0x60, 0x69,
    0x23, 0x76, 0x62, 0x23, 0xB6, 0x5A, 0x49, 0x2A, 0x3B, 0xC1, 0x26, 0x8D, 0x8D, 0xB1, 0xF3, 0x5B,
    0xEC, 0x63, 0xB1, 0x9C, 0x68, 0x72, 0x47, 0x76, 0xB6, 0x9D, 0x1F, 0x33, 0xCB, 0xCC, 0x2E, 0x00,
    0x18, 0x0C, 0x06, 0xEF, 0x30, 0x84, 0xC4, 0x44, 0x04, 0x7E, 0xC8, 0x10, 0x52, 0x97, 0xC6, 0xE7,
    0xA4, 0x84, 0x3E, 0xC4, 0x50, 0xA3, 0x29, 0x49, 0xC3, 0x63, 0x32, 0x1F, 0x62, 0x48, 0xD9, 0x91,
    0x72, 0xC9, 0xFA, 0x11, 0x43, 0x46, 0x5B, 0xC2, 0x9B, 0x18, 0x32, 0x3A, 0x12, 0xDE, 0xE4, 0x0F,
    0xF0, 0x23, 0xFF, 0x80, 0x0F, 0x99, 0x00, 0xB3, 0xC9, 0x14, 0x98, 0x45, 0x4A, 0x80, 0x23, 0xAF,
    0x47, 0x24, 0x04, 0x55, 0xC0, 0xBA, 0x34, 0x97, 0x5A, 0x1C, 0x16, 0x89, 0xA6, 0x6B, 0xFC, 0x82,
    0x5C, 0xEF, 0xA3, 0x5C, 0xE8, 0xF2, 0xEB, 0xFE, 0x81, 0x33, 0xFA, 0xEC, 0xB1, 0x4C, 0x5C, 0x09,
    0x72, 0xC9, 0xDE, 0x3D, 0x5E, 0x8C, 0x5D, 0x0D, 0x7A, 0x74, 0x68, 0x52, 0x2F, 0xBB, 0x85, 0x9B,
    0xB4, 0x95, 0xE5, 0x94, 0x13, 0xD9, 0x5C, 0xE8, 0xEA, 0xE3, 0x6D, 0x40, 0xA3, 0x6A, 0x19, 0x0D,
    0x29, 0xDB, 0xB2, 0xF4, 0xE9, 0xD2, 0x7D, 0xBA, 0x1D, 0x7C, 0xA2, 0x5C, 0xDF, 0x43, 0x56, 0xCB,
    0xDA, 0x71, 0xA0, 0xC6, 0x3A, 0xBB, 0xB4, 0x69, 0xB2, 0x45, 0xCF, 0xD5, 0x90, 0x65, 0x83, 0x5A,
    0x15, 0x08, 0xC9, 0x58, 0x62, 0x9E, 0x84, 0x05, 0x3A, 0xCF, 0x37, 0xB2, 0xB2, 0x2F, 0xD7, 0x6C,
    0x56, 0x01, 0x47, 0x22, 0x42, 0x02, 0xE6, 0x58, 0xE3, 0x80, 0x3E, 0x87, 0xEC, 0xB3, 0x52, 0xD5,
    0x52, 0x81, 0xC0, 0x10, 0x90, 0xD2, 0xA0, 0x45, 0x8B, 0x06, 0x69, 0xD9, 0xD0, 0x26, 0xC3, 0x10,
    0x10, 0x93, 0x90, 0x10, 0xFB, 0xBE, 0xF0, 0xE2, 0x07, 0xF1, 0x4C, 0xF6, 0x88, 0x1F, 0xEA, 0xC7,
    0xA7, 0xF4, 0x03, 0x23, 0x37, 0x5D, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42,
    0x60, 0x82 
};

UINT8 PointerImage2x[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x50, 0x08, 0x04, 0x00, 0x00, 0x00, 0xE6, 0x28, 0x7E,
    0xA2, 0x00, 0x00, 0x03, 0x3B, 0x49, 0x44, 0x41, 0x54, 0x68, 0xDE, 0xED, 0xD8, 0x4F, 0x68, 0x1C,
    0x65, 0x1C, 0x87, 0xF1, 0x67, 0xDE, 0x99, 0xDD, 0x99, 0xDD, 0xC9, 0x26, 0xBB, 0xC9, 0x36, 0x69,
    0xB2, 0xE9, 0x9F, 0xDD, 0x54, 0x23, 0x69, 0x8C, 0x92, 0xA0, 0x6D, 0x59, 0x52, 0x6C, 0x75, 0xDB,
    0x0A, 0x25, 0x88, 0x67, 0xEB, 0xA1, 0x08, 0x42, 0x11, 0xF1, 0x20, 0x5E, 0x5A, 0xC8, 0x25, 0xF4,
    0x20, 0xE9, 0xA5, 0xA0, 0x47, 0x0F, 0xA2, 0x55, 0x9B, 0x1A, 0x2F, 0x2A, 0x42, 0xAF, 0x5E, 0x8A,
    0xB4, 0x45, 0xD4, 0x5E, 0xB4, 0x78, 0xA8, 0xD0, 0x88, 0x54, 0xB4, 0x69, 0xD7, 0x84, 0x98, 0xFD,
    0x7A, 0x98, 0x31, 0xA4, 0x24, 0x4D, 0x42, 0x76, 0x26, 0xA0, 0xCC, 0x73, 0x9A, 0xDB, 0x87, 0x99,
    0x7D, 0xF7, 0x9D, 0xF7, 0x37, 0x90, 0xF4, 0xFF, 0xCA, 0xC2, 0x92, 0x83, 0x85, 0xB5, 0x55, 0x9C,
    0xC1, 0x6E, 0x4C, 0x9D, 0x77, 0xB1, 0x31, 0xF1, 0xA3, 0x16, 0x06, 0x07, 0x57, 0x5A, 0xB8, 0x74,
    0xC2, 0x27, 0x85, 0x1D, 0x37, 0x69, 0x61, 0xE3, 0x91, 0x93, 0xA4, 0xB9, 0xE9, 0x6A, 0x8E, 0x74,
    0xDC, 0xA4, 0x45, 0x0A, 0x9F, 0x0E, 0x29, 0x20, 0xF7, 0xB5, 0xC6, 0x4D, 0x1A, 0xD2, 0xB4, 0xB2,
    0x5D, 0x92, 0xFE, 0x94, 0x54, 0xFF, 0x2C, 0x6E, 0xD2, 0xE0, 0x92, 0x67, 0x87, 0x24, 0x1D, 0xDA,
    0x12, 0xD2, 0xE0, 0xD1, 0xCE, 0x6E, 0x49, 0x42, 0x87, 0x03, 0x32, 0xD6, 0x07, 0x1B, 0x80, 0xE5,
    0x00, 0xDC, 0x0A, 0x32, 0x00, 0x2B, 0xFF, 0x82, 0xE8, 0xB0, 0xEE, 0x4A, 0xAA, 0x7F, 0x1A, 0x17,
    0xB9, 0x02, 0x44, 0xCF, 0xC5, 0x4A, 0xAE, 0x02, 0x2E, 0x91, 0x97, 0xE2, 0x20, 0x57, 0x05, 0xE3,
    0x24, 0x1F, 0x02, 0xA2, 0x5A, 0x40, 0x4E, 0x45, 0x4D, 0x3E, 0x14, 0x44, 0x35, 0xCD, 0x4A, 0xAA,
    0x4F, 0xF5, 0x47, 0xBA, 0xE1, 0xAD, 0x01, 0x2E, 0x91, 0x17, 0xA3, 0x24, 0xD7, 0x04, 0xD1, 0x91,
    0xC8, 0xC9, 0x75, 0xC0, 0x25, 0xF2, 0x93, 0xA8, 0xC8, 0x75, 0x41, 0x74, 0x34, 0x52, 0x72, 0x03,
    0x20, 0x3A, 0xAA, 0x7B, 0x92, 0xEA, 0x1F, 0x47, 0x41, 0x6E, 0x08, 0x5C, 0x22, 0x3F, 0x6A, 0x9E,
    0xDC, 0x20, 0x88, 0x9E, 0xD7, 0xFD, 0x48, 0xC8, 0x35, 0xC1, 0x9F, 0xB5, 0xB2, 0xFA, 0x85, 0x21,
    0x9F, 0x14, 0x26, 0x42, 0xF0, 0x35, 0x8D, 0x85, 0x57, 0xE3, 0x5A, 0xAD, 0xF9, 0x0F, 0x9E, 0xF1,
    0x36, 0x7F, 0x8F, 0x2B, 0xC0, 0x37, 0xB5, 0xA8, 0xAF, 0xC2, 0xEB, 0x36, 0xDD, 0x97, 0x74, 0xF6,
    0xF5, 0x91, 0x17, 0x9E, 0x3E, 0x7E, 0xE0, 0xD8, 0xE8, 0xB3, 0xB5, 0xEA, 0x8B, 0xC3, 0x27, 0xFB,
    0x27, 0x76, 0x8C, 0x64, 0x71, 0x22, 0x02, 0xCF, 0xA8, 0x21, 0xE9, 0x6F, 0x55, 0x42, 0xF2, 0x43,
    0x49, 0x3F, 0x4D, 0x73, 0x90, 0xFD, 0x8C, 0xF0, 0x04, 0x03, 0x54, 0xE8, 0xA1, 0x40, 0x26, 0x22,
    0x70, 0x42, 0x92, 0xF4, 0xC7, 0x4D, 0xE9, 0x7C, 0x08, 0xEE, 0x93, 0xB4, 0x38, 0x3B, 0x5A, 0x65,
    0x2F, 0x8F, 0x52, 0x66, 0x27, 0xDD, 0x74, 0x90, 0xC3, 0x8D, 0xE4, 0x91, 0x9E, 0x93, 0x24, 0x5D,
    0xBF, 0xF0, 0xD6, 0x29, 0xE9, 0x37, 0x99, 0x90, 0xBC, 0x22, 0xE9, 0x87, 0x71, 0xCA, 0x74, 0x53,
    0xA4, 0x40, 0x1B, 0x2D, 0x78, 0xA4, 0x36, 0x7F, 0x46, 0x5F, 0x06, 0x4A, 0xD2, 0xD5, 0xF7, 0xA8,
    0x51, 0xBB, 0x73, 0x5D, 0x3A, 0x15, 0x82, 0xAF, 0x48, 0x9A, 0xBB, 0x41, 0x2F, 0xED, 0xB4, 0xE0,
    0xE1, 0x92, 0xC2, 0x69, 0x66, 0x24, 0x58, 0x76, 0x88, 0x92, 0xAE, 0xBE, 0xC3, 0x28, 0x07, 0xA8,
    0x7E, 0x71, 0x46, 0xBA, 0x16, 0x82, 0x96, 0x66, 0x24, 0x7D, 0x3D, 0x46, 0x1E, 0x0F, 0x07, 0x83,
    0x69, 0x6E, 0xEC, 0x31, 0xB8, 0x14, 0xD8, 0x25, 0xA9, 0x71, 0x6D, 0x92, 0xA7, 0x78, 0x92, 0x41,
    0x86, 0x5A, 0xF7, 0xCF, 0xCD, 0x48, 0x07, 0x43, 0xF2, 0x9C, 0xA4, 0xBB, 0xD3, 0xB4, 0xE3, 0x61,
    0x47, 0x75, 0x10, 0xEE, 0xD5, 0xE2, 0x77, 0xE3, 0x0C, 0xF1, 0x18, 0x15, 0x76, 0xD1, 0xC7, 0xE0,
    0x8D, 0x77, 0xA5, 0x8B, 0x21, 0x58, 0xD2, 0xBC, 0x1A, 0xF3, 0x93, 0x03, 0xB4, 0x6C, 0x7E, 0x6D,
    0x3E, 0x78, 0xD4, 0xCF, 0xD1, 0xF5, 0xE3, 0x1B, 0xEC, 0xA1, 0x42, 0x2F, 0x9D, 0x14, 0xD9, 0x4E,
    0xDF, 0xCB, 0x87, 0x1A, 0xF3, 0x7F, 0xA9, 0x18, 0x92, 0x97, 0x25, 0xCD, 0x9C, 0xA5, 0x0D, 0x77,
    0xF3, 0x3B, 0xCC, 0xF2, 0x61, 0x26, 0x4B, 0x81, 0x2E, 0xBA, 0xE9, 0xA4, 0x40, 0x0E, 0x9F, 0x3C,
    0x25, 0x06, 0x6E, 0x7F, 0x29, 0x4D, 0xC8, 0xE8, 0x55, 0x7D, 0x23, 0x49, 0x5A, 0xB8, 0xD5, 0x53,
    0x24, 0xD3, 0xFC, 0x43, 0xB5, 0xB0, 0x71, 0xF1, 0x69, 0xA5, 0x8D, 0x1C, 0x19, 0xD2, 0xA4, 0xF1,
    0xD9, 0x46, 0xDF, 0xFB, 0x27, 0xA4, 0x3B, 0xFA, 0x35, 0x5C, 0xBD, 0x0B, 0x33, 0xBF, 0x4C, 0x8E,
    0xF5, 0x90, 0x8D, 0xE6, 0x15, 0xEC, 0x90, 0xC6, 0xC5, 0x25, 0x8D, 0x83, 0xC1, 0x0E, 0x7E, 0x55,
    0x06, 0x67, 0xBF, 0x0F, 0xB0, 0xDF, 0xBF, 0xBD, 0x7C, 0xBA, 0x38, 0x4C, 0x99, 0x0E, 0x32, 0x51,
    0x80, 0x16, 0x06, 0x83, 0x1D, 0x0E, 0xDC, 0x16, 0x16, 0x0E, 0x3E, 0x9D, 0xF4, 0x5D, 0x39, 0xBD,
    0x38, 0x77, 0xEB, 0xF3, 0xB7, 0x4F, 0x52, 0x65, 0x98, 0x7E, 0x4A, 0xE4, 0xF1, 0xA2, 0x3A, 0x4A,
    0x59, 0x0F, 0xFC, 0xB7, 0x82, 0x7B, 0x2C, 0x0D, 0xEC, 0x7D, 0x69, 0x94, 0x11, 0x86, 0x79, 0x9C,
    0x47, 0xE8, 0xA5, 0x83, 0xA6, 0x5E, 0x4B, 0xEB, 0x2F, 0xA4, 0x76, 0x4A, 0x94, 0xD9, 0x43, 0x85,
    0x9D, 0x74, 0x51, 0xC0, 0x8F, 0x6F, 0x84, 0xB3, 0x30, 0xA4, 0xF1, 0xC9, 0x53, 0x64, 0x1B, 0x45,
    0x0A, 0xE1, 0xFE, 0x19, 0xE3, 0x5C, 0x6C, 0x61, 0x93, 0xC2, 0x23, 0x4B, 0x96, 0x0C, 0x2E, 0xA9,
    0xF8, 0x3F, 0xA9, 0x58, 0x18, 0x6C, 0x1C, 0x9C, 0xAD, 0xF9, 0x7A, 0xB3, 0xDA, 0x52, 0x4A, 0x4A,
    0x4A, 0x4A, 0x4A, 0x4A, 0x4A, 0x4A, 0x4A, 0x4A, 0x4A, 0x4A, 0x4A, 0x4A, 0xFA, 0xEF, 0xF5, 0x0F,
    0x6B, 0xE8, 0x96, 0x73, 0x50, 0x00, 0x9A, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44,
    0xAE, 0x42, 0x60, 0x82 
};

EFI_STATUS
EFIAPI
FvGetVolumeAttributes (
                       IN  EFI_FIRMWARE_VOLUME_PROTOCOL  *This,
                       OUT FRAMEWORK_EFI_FV_ATTRIBUTES   *Attributes
                       )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FvSetVolumeAttributes (
                       IN EFI_FIRMWARE_VOLUME_PROTOCOL     *This,
                       IN OUT FRAMEWORK_EFI_FV_ATTRIBUTES  *Attributes
                       )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FvReadFile (
            IN EFI_FIRMWARE_VOLUME_PROTOCOL   *This,
            IN EFI_GUID                       *NameGuid,
            IN OUT VOID                       **Buffer,
            IN OUT UINTN                      *BufferSize,
            OUT EFI_FV_FILETYPE               *FoundType,
            OUT EFI_FV_FILE_ATTRIBUTES        *FileAttributes,
            OUT UINT32                        *AuthenticationStatus
            )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FvReadSection (
               IN EFI_FIRMWARE_VOLUME_PROTOCOL   *This,
               IN EFI_GUID                       *NameGuid,
               IN EFI_SECTION_TYPE               SectionType,
               IN UINTN                          SectionInstance,
               IN OUT VOID                       **Buffer,
               IN OUT UINTN                      *BufferSize,
               OUT UINT32                        *AuthenticationStatus
               )
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  if (!Buffer || !BufferSize || !AuthenticationStatus) {
    return EFI_INVALID_PARAMETER;
  }

  if (CompareGuid (NameGuid, &gArrowCursorImageGuid)) {
    *BufferSize = sizeof(PointerImage1x);
    Status = gBS->AllocatePool(EfiBootServicesData, *BufferSize, (VOID **)Buffer);
    if (!EFI_ERROR(Status)) {
      CopyMem(*Buffer, &PointerImage1x, *BufferSize);
    }
    *AuthenticationStatus = 0;
    return Status;
  } else if (CompareGuid (NameGuid, &gArrowCursor2xImageGuid)) {
    *BufferSize = sizeof(PointerImage2x);
    Status = gBS->AllocatePool(EfiBootServicesData, *BufferSize, (VOID **)Buffer);
    if (!EFI_ERROR(Status)) {
      CopyMem(*Buffer, &PointerImage2x, *BufferSize);
    }
    *AuthenticationStatus = 0;
    return Status;
  } else if (CompareGuid (NameGuid, &gGuidListGuid)) {
    *BufferSize = sizeof(GuidList);
    Status = gBS->AllocatePool(EfiBootServicesData, *BufferSize, (VOID **)Buffer);
    if (!EFI_ERROR(Status)) {
      CopyMem(*Buffer, &GuidList, *BufferSize);
    }
    *AuthenticationStatus = 0;
    return Status;
  }

  *AuthenticationStatus = EFI_LOCAL_AUTH_STATUS_TEST_FAILED;
  return EFI_NOT_FOUND;
}

EFI_STATUS
EFIAPI
FvWriteFile (
             IN EFI_FIRMWARE_VOLUME_PROTOCOL      *This,
             IN UINT32                            NumberOfFiles,
             IN FRAMEWORK_EFI_FV_WRITE_POLICY     WritePolicy,
             IN FRAMEWORK_EFI_FV_WRITE_FILE_DATA  *FileData
             )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FvGetNextFile (
               IN EFI_FIRMWARE_VOLUME_PROTOCOL   *This,
               IN OUT VOID                       *Key,
               IN OUT EFI_FV_FILETYPE            *FileType,
               OUT EFI_GUID                      *NameGuid,
               OUT EFI_FV_FILE_ATTRIBUTES        *Attributes,
               OUT UINTN                         *Size
               )
{
  return EFI_SUCCESS;
}

EFI_FIRMWARE_VOLUME_PROTOCOL   FirmwareVolume = {
  FvGetVolumeAttributes,
  FvSetVolumeAttributes,
  FvReadFile,
  FvReadSection,
  FvWriteFile,
  FvGetNextFile,
  16,    //KeySize
  NULL  //ParentHandle
};

/****************************************************************
 * Entry point
 ***************************************************************/

/**
 * FirmwareVolume entry point. Installs AppleGraphConfigProtocol.
 */
EFI_STATUS
EFIAPI
FVEntrypoint (IN EFI_HANDLE           ImageHandle,
              IN EFI_SYSTEM_TABLE		*SystemTable
              )
{
  EFI_STATUS					            Status; 
  EFI_FIRMWARE_VOLUME_PROTOCOL    *ExistingFirmwareVolume;
  
  Status = gBS->LocateProtocol (&gEfiFirmwareVolumeProtocolGuid, NULL, (VOID **)&ExistingFirmwareVolume);

  if (EFI_ERROR(Status)) {
    Status = gBS->InstallMultipleProtocolInterfaces (
                                                     &mHandle2,
                                                     &gEfiFirmwareVolumeProtocolGuid,
                                                     &FirmwareVolume,
                                                     NULL
                                                     );
  } else {
    ExistingFirmwareVolume->GetVolumeAttributes = FvGetVolumeAttributes;
    ExistingFirmwareVolume->SetVolumeAttributes = FvSetVolumeAttributes;
    ExistingFirmwareVolume->ReadFile            = FvReadFile;
    ExistingFirmwareVolume->ReadSection         = FvReadSection;
    ExistingFirmwareVolume->WriteFile           = FvWriteFile;
    ExistingFirmwareVolume->GetNextFile         = FvGetNextFile;
  }
  
  return Status;
}

