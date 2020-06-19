#pragma once

// make FILETIME easy serializable
template <class TStream>
TStream& operator<<(TStream& stm, const FILETIME& ft)
{
	stm << ((static_cast <uint64_t> (ft.dwHighDateTime) << 32) | ft.dwLowDateTime);
	return stm;
}
template <class TStream>
TStream& operator>>(TStream& stm, FILETIME& ft)
{
	uint64_t u;
	stm >> u;
	ft.dwHighDateTime = (DWORD) (u >> 32);
	ft.dwLowDateTime = (DWORD) u;
	return stm;
}