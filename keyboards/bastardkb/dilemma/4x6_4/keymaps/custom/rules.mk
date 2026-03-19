# Basic Features
ENCODER_MAP_ENABLE = yes
TAP_DANCE_ENABLE = yes

# Quantum Painter Configuration
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += gc9a01_spi

# Pathing: This tells the compiler to look inside your generated folder
VPATH += generated

# Source Files: Do NOT use absolute paths here
SRC += generated/ring.qff.c
SRC += generated/logo.qgf.c
