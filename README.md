# Active Voltage Quadrupler Rectifier-Based Ultra-High Boost Ratio Multidirectional Energy Router in 800V DC Microgrids

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

📢 **This work has been published in IEEE Access**: [https://ieeexplore.ieee.org/document/11008631](https://ieeexplore.ieee.org/document/11008631)

License: MIT Open Source (Commercial use permitted with attribution)  
Maintainer: Yuchong Peng | Last Update: 2025-03  

---

# 基于有源电压四倍整流器的超高升压比多端口能量路由器在800V直流微网中的应用

本仓库为一款高效率三端口能量路由器提供完整的开源资源，适用于800V直流微网环境。系统实现了光伏组件（15–25V）、储能电池（40–50V）与800V母线之间的智能能量管理，具备以下三项关键技术：

**核心创新**  
1. **混合拓扑**  
   - 采用交错升压转换器与有源电压四倍单元（VQC）相结合  
   - MOSFET电压应力降低50%（从传统的800V降至400V）  
   - 实现<3ms的双向能量流动模式切换  

2. **磁集成设计**  
   - 利用漏感作为功能性参数  
   - 总磁性器件体积减少36%（从203.6 cm³降至136.1 cm³）  
   - 保持宽范围ZVS软开关工作状态  

3. **自适应控制策略**  
   - 融合PWM与相移调制（PSM）  
   - 在20–100%负载范围内实现97.5%的峰值效率  
   - 支持6种工作模式的无缝切换  

**实验验证**  
500W样机实测表现如下：  
- 面对95%阶跃负载变化时维持稳定运行  
- 在光伏/电池模式切换过程中直流母线电压偏差<2%  
- 额定功率下总损耗为12.5W  

**仓库内容**  
- 📁 `Simulation`: SIMULINK仿真结果  
- 📁 `Hardware Design`: PCB布局、物料清单、磁件参数  
- 📁 `Control Firmware`: TMS320F28379D控制固件源码  
- 📁 `Test Data`:  
  - 超过50小时的示波器工作波形  
  - 不同光伏电压下的效率曲线  
- 📁 `Paper`: 提交IEEE Access的论文和LaTeX工程文件  
- 📁 `PDF in latex of TPC`: 论文中使用的PDF图文件  
- 📁 `Experiments Notebook/`: 实验日志与进度记录  
- 📁 `RMS Current`: RMS电流计算结果及图像  
- 📁 `ZVS`: ZVS计算结果及图像  

**社区贡献建议**  
我们欢迎科研人员：  
1. 使用Jupyter笔记本（`/Analysis/Parameter_Sweep.ipynb`）验证本设计  
2. 优化最大功率点跟踪（MPPT）算法  
3. 扩展本拓扑至更大功率等级的应用  

📢 **该研究成果已发表在IEEE Access期刊**：[https://ieeexplore.ieee.org/document/11008631](https://ieeexplore.ieee.org/document/11008631)

许可证：MIT开源协议（允许商业使用并需注明来源）  
维护者：彭宇冲 | 最后更新：2025-03
