enum tiles_t
{
	m_temp_firefloor = -3,
	m_firefloor = -2,
	m_manager = -1,
	m_defaultWall = 0,
	m_exit,
	m_pressure,
	m_floor,
	m_wall,
	m_conveyore,
	m_conveyorn,
	m_conveyors,
	m_conveyorw,
	m_barrier,
	m_icefloor,
	m_bomb,
	m_toggleOff,
	m_toggleOn,
	m_dupeN,
	m_dupeW,
	m_dupeS,
	m_dupeE,
	m_blackHole,
	m_raisedFloor,
	m_electricFloor,
	m_electricFloorOff,
	m_water,
	m_freezerFloor,
	m_freezerFloorOff,
	m_unused,
	m_bounceWall,
	m_risingWall,
	m_oilspill,
	m_teleSource,
	m_teleDest,
	m_barrierOff,
	m_heaterOn,
	m_heaterOff,

	OBJ_BLOCK = 1001,
	OBJ_HEAVY_BLOCK,
	OBJ_ICE_BLOCK,
	OBJ_PLAYER,
	OBJ_ICE_ELEMENT_E,
	OBJ_ICE_ELEMENT_N,
	OBJ_ICE_ELEMENT_S,
	OBJ_ICE_ELEMENT_W,
	OBJ_PICKUP,
	OBJ_PICKUP_WALL,
	OBJ_UNUSED,
	OBJ_FLAME,
	OBJ_PIPE_NW,
	OBJ_PIPE_SW,
	OBJ_PIPE_SE,
	OBJ_PIPE_NE,
	OBJ_MAGNET_N,
	OBJ_MAGNET_S,
	OBJ_MAGNET_W,
	OBJ_MAGNET_E,
	OBJ_FIRE_ELEMENT_E,
	OBJ_FIRE_ELEMENT_N,
	OBJ_FIRE_ELEMENT_S,
	OBJ_FIRE_ELEMENT_W,
	OBJ_OIL_BARREL,
	OBJ_BOULDER,
	OBJ_PUSHER_E,
	OBJ_PUSHER_N,
	OBJ_PUSHER_S,
	OBJ_PUSHER_W,
	OBJ_BARRIER_BLOCK_1,
	OBJ_BARRIER_BLOCK_2,
	OBJ_BARRIER_BLOCK_3,
	OBJ_BARRIER_BLOCK_4,
	OBJ_BARRIER_1,
	OBJ_BARRIER_2,
	OBJ_BARRIER_3,
	OBJ_BARRIER_4,
	OBJ_CRYSTAL_BLOCK,
	OBJ_CRYSTAL_WALL,

	m_sender1 = 2001,
	m_receiver1,
	m_sender2,
	m_receiver2,
	m_sender3,
	m_receiver3,
	m_sender4,
	m_receiver4,

	m_any,
	m_error = 0
};