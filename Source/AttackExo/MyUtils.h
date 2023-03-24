
#pragma once

#define WORLD GetWorld()
#define DELTATIME GetWorld()->DeltaTimeSeconds

#define OWNER GetOwner()
#define FPC GetWorld()->GetFirstPlayerController()
#define PAWN GetWorld()->GetFirstPlayerController()->GetPawn()

#define CREATE(type, name) CreateDefaultSubobject<type>(name)
#define ATTACH_TO(attach, to) attach->SetupAttachment(to)

#define DRAW_SPHERE(location, radius, segments, color, thickness) DrawDebugSphere(GetWorld(), location, radius, segments, color, false, -1.0f, 0, thickness)
#define DRAW_LINE(start, end, color, thickness) DrawDebugLine(GetWorld(), start, end, color, false, -1.0f, 0, thickness)
#define DRAW_BOX(location, extent, color, thickness) DrawDebugBox(GetWorld(), location, extent, color, false, -1.0f, 0, thickness)

#define LERP(from, to, t) FMath::Lerp(from, to, t)

#define FORWARD "FORWARD"
#define ROTATION "ROTATION"
#define POSSESS "POSSESS"
#define SWITCH "SWITCH"