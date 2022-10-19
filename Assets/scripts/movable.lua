
e = world:getEntity(entity_id)
vel = e:getVelocity()
jump_speed = e:getJumpSpeed()
pos = e:getPosition()
plane = e:getBouncePlane()
input = input_handler:getInputState()

speed = 10.0
deltaVel   = {
	x = 0.0,
	y = 0.0,
	z = 0.0
}
plane_epsilon = 0.1;

if input:test(eIC_GoLeft) then
	deltaVel.x = deltaVel.x - speed
end
if input:test(eIC_GoRight) then
	deltaVel.x = deltaVel.x + speed
end

if input:test(eIC_Jump) then
	if plane.x * pos.x + plane.y * pos.y + plane.z * pos.z < plane.w + plane_epsilon then
		vel.y = jump_speed
	end
end

vel.x = vel.x + deltaVel.x * delta_time
vel.z = vel.z + deltaVel.z * delta_time