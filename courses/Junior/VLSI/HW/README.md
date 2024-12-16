# Six Gates
1. INV  
2. NAND
3. NOR
4. AND
5. OR
6. XOR


INV for example
1. schematic  
因為 `μₙ = 1350 cm²/V．s`, `μₚ = 480 cm²/V．s` -> `μₙ ≈ 2.5μₚ`，所以為了讓 `mos` 飽和區電流相同。會將 `pmos` 的 `w` 畫成 `nmos` 的三倍(2.5取整數，因為數位ic以 `w` 為單位)
- `nmos`
![nmos](https://github.com/codingpeanut/peanut-universe/blob/main/courses/Junior/VLSI/assets/INV_param_nmos.png)
- `pmos`
![pmos](https://github.com/codingpeanut/peanut-universe/blob/main/courses/Junior/VLSI/assets/INV_param_pmos.png)

2. simulation
- `vdc = 1.8V`
![vdc1.8](https://github.com/codingpeanut/peanut-universe/blob/main/courses/Junior/VLSI/assets/INV_simu_param_vdc1.png)
- `vdc = 0V`
![vdc0](https://github.com/codingpeanut/peanut-universe/blob/main/courses/Junior/VLSI/assets/INV_simu_param_vdc_2.png)
- `vpulse`
![vdc1.8](https://github.com/codingpeanut/peanut-universe/blob/main/courses/Junior/VLSI/assets/INV_simu_param_vpulse_1.png)
![vdc1.8](https://github.com/codingpeanut/peanut-universe/blob/main/courses/Junior/VLSI/assets/INV_simu_param_vpulse_2.png)
