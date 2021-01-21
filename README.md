# Embedded-systems-design-projects

## First Project

Modeling and synthesis of a floating-point single precision multiplier in three different ways:
1. Two different modules connected in one platform, one in Verilog and the other one in VHDL ([`VHDL_verilog`](first-project/solutions/RTL/VHDL_verilog));
2. One module in [`SystemC`](first-project/solutions/RTL/SystemC);
3. A simple multiplier in [`C++`](first-project/solutions/RTL/cpp).

All the informations and the comparisons are available in the [`report](first-project/report).

## Second Project

Modeling and synthesis of a floating-point single precision multiplier in different ways:
1. Untimed SystemC TLM multiplier ([`UT`](second-project/solutions/TLM/UT));
2. Loosely-timed SystemC TLM multiplier ([`LT`](second-project/solutions/TLM/LT));
3. Approximately-timed SystemC TLM multiplier ([`AT4`](second-project/solutions/TLM/AT4));
4. Integration of VHDL and Verilog multipliers in a [`Virtual Platform`](second-project/solutions/Virtual_Platform).

All the informations and the comparisons are available in the [`report](second-project/report).