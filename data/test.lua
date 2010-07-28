
print("lua test")

x = 0
y = 0
vx = 1
vy = 1

function update()

	x = x + vx
	y = y + vy

	if x <= 0 or x >= getWidth()-1 then
		vx = -(vx)
	end
	if y <= 0 or y >= getHeight()-1 then
		vy = -(vy)
	end

end

function draw()
	stroke(0xFF0000)
	line(x, 0, x, getHeight()-1)

	stroke(0x00FF00)
	line(0, y, getWidth()-1, y)

	stroke(0xFFFFFF)
	rect(x, y, 1, 1)
end

