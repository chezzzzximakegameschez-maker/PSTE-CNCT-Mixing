#include "simulation/ElementCommon.h"
static int update(UPDATE_FUNC_ARGS);
void Element::Element_PSTE() {
	Identifier = "DEFAULT_PT_PSTE";
	Name = "PSTE";
	Colour = 0xAA99AA_rgb;
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 18;

	Weight = 31;
	DefaultProperties.tmp = 1;
	DefaultProperties.temp = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 29;
	Description = "Colloid, Hardens under pressure.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 0.5f;
	HighPressureTransition = ST;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 747.0f;
	HighTemperatureTransition = PT_BRCK;

	Update = &update;
}
static int update(UPDATE_FUNC_ARGS) {
	if (parts[i].tmp == 1) {
		for (int rx = -1; rx <= 1; rx++) {
			for (int ry = -1; ry <= 1; ry++) {
				if (rx || ry) {
					auto r = pmap[y + ry][x + rx];
					if(TYP(r) == PT_SAND && parts[i].ctype != PT_CNCT){
						sim->kill_part(ID(r));
						parts[i].ctype = PT_CNCT;
					}
				}
			}
		}
	}
	return 0;
}