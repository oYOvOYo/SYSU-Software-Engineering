@echo off
set xv_path=F:\\Xilinx_Vivado_SDK_2015.2_0626_1\\installed\\Vivado\\2015.2\\bin
echo "xvlog -m64 --relax -prj CPU_sim_vlog.prj"
call %xv_path%/xvlog  -m64 --relax -prj CPU_sim_vlog.prj -log compile.log
if "%errorlevel%"=="1" goto END
if "%errorlevel%"=="0" goto SUCCESS
:END
exit 1
:SUCCESS
exit 0
