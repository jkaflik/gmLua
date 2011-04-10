local car = false     -- Car instance ID
local fuel = 1        -- Almost out of gas!

function onCreate(id) -- onCreate event with one argument which is car instance id
	car = id
	showMessage("Welcome from our example script, have fun :)")
end

function onKey(key)
	if (key == 32) then			-- Spacebar, you need to find keycodes yourself.
		                        -- Check that car is in the area, the magical place where you gain fuel.
		if (getX(car) > 1104 and getY(car) > 384 and getX(car) < 1248 and getY(car) < 448) and fuel <= 49.5 then
			fuel = fuel + 0.25  -- Get some fuel
		end
	end
end

function onDraw()
	-- Draw fuel amount below the car
	drawText(getX(car) - 20, getY(car) - 50, tostring(fuel) .. " litres")
		
	-- Draw some text
	drawText(1105, 369, "Press SPACE to fill your fuel")
	
	drawLine(getX(car), getY(car), 1170, 400)
end

function onMove()
	if (fuel > 0.1) then    -- Do we have enough fuel to move? o.0
		fuel = fuel - 0.005 -- Yes, use some fuel.
	else
		return 1            -- If not, tell the game we're out.
	end
end

-- For teh lulz.
function test(str)
	return str .. " is nice!"
end
