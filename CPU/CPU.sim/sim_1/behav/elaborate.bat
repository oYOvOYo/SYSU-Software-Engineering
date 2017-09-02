@echo off
set xv_path=F:\\Xilinx_Vivado_SDK_2015.2_0626_1\\installed\\Vivado\\2015.2\\bin
call %xv_path%/xelab  -wto d73a359c4072432ea3aa0df8763a960b -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot CPU_sim_behav xil_defaultlib.CPU_sim xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
