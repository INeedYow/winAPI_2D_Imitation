#pragma once

DIR collisionRectToRect(const fPoint& pos1, const fPoint& size1, const fPoint& pos2, const fPoint& size2);

bool isCollisionRectToRect(const fPoint& pos1, const fPoint& size1, const fPoint& pos2, const fPoint& size2);
bool isCollisionPointToRect(const fPoint& point, const RECT& rt);
bool isCollisionPointToCircle(const fPoint& point, const fPoint& cp, int cr);
bool isCollisionCircleToRect(const fPoint& cp, int cr, const RECT& rt);
bool isCollisionCircleToCircle(const fPoint& cp1, int cr1, const fPoint& cp2, int cr2);