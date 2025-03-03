# Energy Router for 800V DC Microgrids: Design, Implementation, and Validation

This repository provides full open-access resources for a high-efficiency three-port energy router targeting 800V DC microgrid applications. The system enables intelligent power management between photovoltaic (PV) panels (15-25V), energy storage batteries (40-50V), and an 800V DC bus through three key technological advancements:

**Core Innovations**  
1. **Hybrid Topology**  
   - Integrates interleaved boost converter with active voltage quadrupler cell (VQC)  
   - Achieves 50% reduction in MOSFET voltage stress (400V vs conventional 800V)  
   - Enables multidirectional power flow with <3ms mode transitions  

2. **Magnetic Integration**  
   - Implements leakage inductance utilization technique  
   - Reduces total magnetic component volume by 36% (203.6 cm³ → 136.1 cm³)  
   - Maintains wide zero-voltage switching (ZVS) operation range  

3. **Adaptive Control**  
   - Combines PWM and phase-shift modulation (PSM)  
   - Achieves 97.5% peak efficiency across 20-100% load range  
   - Supports seamless transitions between 6 operating modes  

**Experimental Validation**  
A 500W prototype demonstrates:  
- Stable operation under 95% step load changes  
- <2% DC bus voltage deviation during PV/battery mode switching  
- 12.5W total losses at rated power 

**Repository Contents**  
- 📁 `Simulation`: SIMULINK simulation results
- 📁 `Hardware Design`: PCB layouts, BOM, magnetics specifications  
- 📁 `Control Firmware`: Digital control code for TMS320F28379D  
- 📁 `Test Data`:  
  - 50+ hours of operational waveforms (Tektronix captures)  
  - Efficiency curves under 15-25V PV input conditions  
- 📁 `Paper`: Manuscript submitted to IEEE Access and compilable LaTeX project files
- 📁 `PDF in latex of TPC`: these pdf files are used in the Paper
- 📁 `Experiments Notebook/`: Daily experimental progress
- 📁 `RMS Current`: RMS theoretical calculation results and drawing
- 📁 `ZVS`: ZVS theoretical calculation results and drawing

**Community Contribution**  
We encourage researchers to:  
1. Validate the design through our interactive Jupyter notebook (`/Analysis/Parameter_Sweep.ipynb`)  
2. Improve the maximum power point tracking (MPPT) algorithm  
3. Extend the topology for higher power applications  

License: MIT Open Source (Commercial use permitted with attribution)  
Maintainer: Yuchong Peng| Last Update: 2025-03  
