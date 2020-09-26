// DSP instructions:
// This is just an attempt at trying to figure out what the AICA DSP instructions are
// based on what the Reicast emulator does...

Bank[0]
#define TRA (0x7f << 9)
#define TWT (1 << 8)
#define TWA (0x7f << 1)

Bank[1]
#define XSEL (1 << 15)
#define YSEL (3 << 13)
#define IRA (0x3f << 7)
#define IWT (1 << 6)
#define IWA (0x1f << 1)

Bank[2]
#define TABLE (1 << 15)
#define MWT (1 << 14)
#define MRD (1 << 13)
#define EWT (1 << 12)
#define EWA (0xf << 8)
#define ADRL (1 << 7)
#define FRCL (1 << 6)
#define SHIFT (3 << 4)
#define YRL (1 << 3)
#define NEGB (1 << 2)
#define ZERO (1 << 1)
#define BSEL (1 << 0)

Bank[3]
#define NOFL (1 << 15)
#define COEF (0x3f << 9) // MASA?
#define MASA COEF
#define ADREB (1 << 8)
#define NXADR (1 << 7)
