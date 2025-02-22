//
//  Transform.m
//  Assignment #5
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Transform.h"


@implementation Transform

- (id)initWithFrame:(NSRect)frame {
	[super initWithFrame:frame];
	x_size = frame.size.width;
	y_size = frame.size.height;
	
	xAxis = TRUE;
	yAxis = FALSE;
	zAxis = FALSE;
	
	// Read Data into our matrices
	if ([self readPoints:[[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/Qpoints3D.dat"]] == NO) {
		NSLog(@"Unable to read Qpoints.dat");
	}
	if ([self readLines:[[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/Qlines3D.dat"]] == NO) {
		NSLog(@"Unable to read Qlines.dat");
	}
	
	[self reset:nil];
	
	return self;
}

- (IBAction)translate_X:(id)sender {
	double x;
	
	if ([sender doubleValue] == 0.0) {
		x = -50.0;
	}
	else {
		x = 50.0;
	}
	
	[m_transform atX:0 atY:3 put:[NSNumber numberWithFloat:x]];
	[m_transform atX:1 atY:3 put:[NSNumber numberWithFloat:0.0]];
	m_product = [Matrix newWithMultiply:m_product m2:m_transform];
	
    [self setNeedsDisplay:YES];
}

- (IBAction)translate_Y:(id)sender {
	double y;
	
	if ([sender doubleValue] == 0.0) {
		y = -25.0;
	}
	else {
		y = 25.0;
	}
	
	[m_transform atX:0 atY:3 put:[NSNumber numberWithFloat:0.0]];
	[m_transform atX:1 atY:3 put:[NSNumber numberWithFloat:y]];
	m_product = [Matrix newWithMultiply:m_product m2:m_transform];
	
    [self setNeedsDisplay:YES];
}

- (IBAction)zoom:(id)sender {
	float x_cen, y_cen, z_cen;
	double z;
	
	if ([sender doubleValue] == 0.0) {
		z = 0.9;
	}
	else {
		z = 1.1;
	}
	
	// Translate the image to 0,0
	x_cen = [[m_draw atX:0 atY:0] floatValue];
	y_cen = [[m_draw atX:1 atY:0] floatValue];
	z_cen = [[m_draw atX:2 atY:0] floatValue];
	[m_transform atX:0 atY:3 put:[NSNumber numberWithFloat:-x_cen]];
	[m_transform atX:1 atY:3 put:[NSNumber numberWithFloat:-y_cen]];
	[m_transform atX:2 atY:3 put:[NSNumber numberWithFloat:-z_cen]];
	m_product = [Matrix newWithMultiply:m_product m2:m_transform];
	
	// Scale the image
	[m_scale atX:0 atY:0 put:[NSNumber numberWithFloat:z]];
	[m_scale atX:1 atY:1 put:[NSNumber numberWithFloat:z]];
	[m_scale atX:2 atY:2 put:[NSNumber numberWithFloat:z]];
	m_product = [Matrix newWithMultiply:m_product m2:m_scale];
	
	// Translate the image back
	[m_transform atX:0 atY:3 put:[NSNumber numberWithFloat:x_cen]];
	[m_transform atX:1 atY:3 put:[NSNumber numberWithFloat:y_cen]];
	[m_transform atX:2 atY:3 put:[NSNumber numberWithFloat:z_cen]];
	m_product = [Matrix newWithMultiply:m_product m2:m_transform];

    [self setNeedsDisplay:YES];
}

- (IBAction)rotate_X:(id)sender {
	double r;
	
	if ([sender doubleValue] == 0.0) {
		r = -0.05;
	}
	else {
		r = 0.05;
	}
	
	// Rotate the image bout the X axis
	[self rotate:TRUE y:FALSE z:FALSE angle:(r)];

    [self setNeedsDisplay:YES];	
}

- (IBAction)rotate_Y:(id)sender {
	double r;
	
	if ([sender doubleValue] == 0.0) {
		r = -0.05;
	}
	else {
		r = 0.05;
	}
	
	// Rotate the image bout the Y axis
	[self rotate:FALSE y:TRUE z:FALSE angle:(r)];
}

- (IBAction)rotate_Z:(id)sender {
	double r;
	
	if ([sender doubleValue] == 0.0) {
		r = -0.05;
	}
	else {
		r = 0.05;
	}

	// Rotate the image bout the Z axis
	[self rotate:FALSE y:FALSE z:TRUE angle:(r)];
}

- (void)rotate:(bool)x y:(bool)y z:(bool)z angle:(double)r {
	float x_cen, y_cen, z_cen;
	
	// Translate the image to 0,0
	x_cen = [[m_draw atX:0 atY:0] floatValue];
	y_cen = [[m_draw atX:1 atY:0] floatValue];
	z_cen = [[m_draw atX:2 atY:0] floatValue];
	[m_transform atX:0 atY:3 put:[NSNumber numberWithFloat:-x_cen]];
	[m_transform atX:1 atY:3 put:[NSNumber numberWithFloat:-y_cen]];
	[m_transform atX:2 atY:3 put:[NSNumber numberWithFloat:-z_cen]];
	m_product = [Matrix newWithMultiply:m_product m2:m_transform];

	if (x) {
		[m_rotate atX:0 atY:0 put:[NSNumber numberWithFloat:1.0]]; // 1
		[m_rotate atX:1 atY:0 put:[NSNumber numberWithFloat:0.0]]; // 0
		[m_rotate atX:2 atY:0 put:[NSNumber numberWithFloat:0.0]]; // 0
		
		[m_rotate atX:0 atY:1 put:[NSNumber numberWithFloat:0.0]]; // 0
		[m_rotate atX:1 atY:1 put:[NSNumber numberWithFloat:cos(r)]]; // cos
		[m_rotate atX:2 atY:1 put:[NSNumber numberWithFloat:-sin(r)]]; // -sin
		
		[m_rotate atX:0 atY:2 put:[NSNumber numberWithFloat:0.0]]; // 0
		[m_rotate atX:1 atY:2 put:[NSNumber numberWithFloat:sin(r)]]; // sin
		[m_rotate atX:2 atY:2 put:[NSNumber numberWithFloat:cos(r)]]; // cos
		m_product = [Matrix newWithMultiply:m_product m2:m_rotate];
	}
	
	if (y) {
		[m_rotate atX:0 atY:0 put:[NSNumber numberWithFloat:cos(r)]]; // cos
		[m_rotate atX:1 atY:0 put:[NSNumber numberWithFloat:0.0]]; // 0
		[m_rotate atX:2 atY:0 put:[NSNumber numberWithFloat:sin(r)]]; // sin
		
		[m_rotate atX:0 atY:1 put:[NSNumber numberWithFloat:0.0]]; // 0
		[m_rotate atX:1 atY:1 put:[NSNumber numberWithFloat:1.0]]; // 1
		[m_rotate atX:2 atY:1 put:[NSNumber numberWithFloat:0.0]]; // 0
		
		[m_rotate atX:0 atY:2 put:[NSNumber numberWithFloat:-sin(r)]]; // -sin
		[m_rotate atX:1 atY:2 put:[NSNumber numberWithFloat:0.0]]; // 0
		[m_rotate atX:2 atY:2 put:[NSNumber numberWithFloat:cos(r)]]; // cos
		m_product = [Matrix newWithMultiply:m_product m2:m_rotate];
	}
	
	if (z) {
		[m_rotate atX:0 atY:0 put:[NSNumber numberWithFloat:cos(r)]]; // cos
		[m_rotate atX:1 atY:0 put:[NSNumber numberWithFloat:-sin(r)]]; // -sin
		[m_rotate atX:2 atY:0 put:[NSNumber numberWithFloat:0.0]]; // 0
		
		[m_rotate atX:0 atY:1 put:[NSNumber numberWithFloat:sin(r)]]; // sin
		[m_rotate atX:1 atY:1 put:[NSNumber numberWithFloat:cos(r)]]; // cos
		[m_rotate atX:2 atY:1 put:[NSNumber numberWithFloat:0.0]]; // 0
		
		[m_rotate atX:0 atY:2 put:[NSNumber numberWithFloat:0.0]]; // 0
		[m_rotate atX:1 atY:2 put:[NSNumber numberWithFloat:0.0]]; // 0
		[m_rotate atX:2 atY:2 put:[NSNumber numberWithFloat:1.0]]; // 1
		m_product = [Matrix newWithMultiply:m_product m2:m_rotate];
	}

	// Translate the image back
	[m_transform atX:0 atY:3 put:[NSNumber numberWithFloat:x_cen]];
	[m_transform atX:1 atY:3 put:[NSNumber numberWithFloat:y_cen]];
	[m_transform atX:2 atY:3 put:[NSNumber numberWithFloat:z_cen]];
	m_product = [Matrix newWithMultiply:m_product m2:m_transform];
	
	[self setNeedsDisplay:YES];
}

- (IBAction)sheer_X:(id)sender {
	float x_min = MAXFLOAT, y_min = MAXFLOAT, z_min = MAXFLOAT;
	bool reanim = FALSE;
	int i;
	double s;
	
	if ([sender doubleValue] == 0.0) {
		s = -0.1;
	}
	else {
		s = 0.1;
	}
		
	if (timer != nil) {
		[timer invalidate];
		[timer release];
		timer = nil;
		reanim = TRUE;
	}
	
	for (i = 0; i < [m_points maxY]; i++) {
		if ([[m_points atX:1 atY:i] floatValue] == 0) {
			y_min = [[m_draw atX:1 atY:i] floatValue];
			if ([[m_points atX:2 atY:i] floatValue] < z_min) {
				z_min = [[m_draw atX:2 atY:i] floatValue];
			}
			if ([[m_points atX:0 atY:i] floatValue] < x_min) {
				x_min = [[m_draw atX:0 atY:i] floatValue];
			}
		}
	}
		
	// Translate lower left to 0,0
	[m_transform atX:0 atY:3 put:[NSNumber numberWithFloat:-x_min]];
	[m_transform atX:1 atY:3 put:[NSNumber numberWithFloat:-y_min]];
	[m_transform atX:2 atY:3 put:[NSNumber numberWithFloat:-z_min]];
	m_product = [Matrix newWithMultiply:m_product m2:m_transform];
	
	// Sheer the image
	[m_sheer atX:0 atY:1 put:[NSNumber numberWithFloat:s]];
	m_product = [Matrix newWithMultiply:m_product m2:m_sheer];
	
	// Translate the image back
	[m_transform atX:0 atY:3 put:[NSNumber numberWithFloat:x_min]];
	[m_transform atX:1 atY:3 put:[NSNumber numberWithFloat:y_min]];
	[m_transform atX:2 atY:3 put:[NSNumber numberWithFloat:z_min]];
	m_product = [Matrix newWithMultiply:m_product m2:m_transform];
	
	if (reanim) {
		[self anim:nil];
		reanim = FALSE;
	}
	
    [self setNeedsDisplay:YES];	
}

- (IBAction)anim:(id)sender {
    if (timer != nil) {
		[timer invalidate];
		[timer release];
		timer = nil;
	}
	else {
		// We schedule a timer for a desired 30fps animation rate.
		// In performAnimation: we determine exactly
		// how much time has elapsed and animate accordingly.
		timer = [[NSTimer scheduledTimerWithTimeInterval:(1.0/30.0)
												  target:self
												selector:@selector(anim_go:)
												userInfo:nil
												 repeats:YES] retain];

		// The next two lines make sure that animation will continue to occur
		// while modal panels are displayed and while event tracking is taking
		// place (for example, while a slider is being dragged).
		[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSModalPanelRunLoopMode];
		[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode];

		lastTime = [NSDate timeIntervalSinceReferenceDate];
	}
}

- (void)anim_go:(NSTimer *)aTimer {
    // We determine how much time has elapsed since the last animation,
    // and we advance the angle accordingly.
    NSTimeInterval thisTime = [NSDate timeIntervalSinceReferenceDate];
    [self rotate:xAxis y:yAxis z:zAxis angle:0.05];
    lastTime = thisTime;
}

- (IBAction)setXaxis:(id)sender {
	xAxis = !xAxis;

	if (timer != nil) {
		[timer invalidate];
		[timer release];
		timer = nil;
		
		[self anim:nil];
	}
}

- (IBAction)setYaxis:(id)sender {
	yAxis = !yAxis;

	if (timer != nil) {
		[timer invalidate];
		[timer release];
		timer = nil;
		
		[self anim:nil];
	}
}

- (IBAction)setZaxis:(id)sender {
	zAxis = !zAxis;

	if (timer != nil) {
		[timer invalidate];
		[timer release];
		timer = nil;
		
		[self anim:nil];
	}
}

- (IBAction)reset:(id)sender {
	int i, j;

	// Stop any animation that is currently running
	if (timer != nil) {
		[timer invalidate];
		[timer release];
		timer = nil;
	}

		// Create identity matrices
	m_transform = [Matrix newWithXRows:4 YRows:4];
	m_rotate = [Matrix newWithXRows:4 YRows:4];
	m_sheer = [Matrix newWithXRows:4 YRows:4];
	m_scale = [Matrix newWithXRows:4 YRows:4];
	m_product = [Matrix newWithXRows:4 YRows:4];
	for (i = 0; i < [m_product maxY]; i++) {
		for (j = 0; j < [m_product maxX]; j++) {
			if (i == j) {
				[m_transform atX:j atY:i put:[NSNumber numberWithFloat:1.0]];
				[m_rotate atX:j atY:i put:[NSNumber numberWithFloat:1.0]];
				[m_sheer atX:j atY:i put:[NSNumber numberWithFloat:1.0]];
				[m_scale atX:j atY:i put:[NSNumber numberWithFloat:1.0]];
				[m_product atX:j atY:i put:[NSNumber numberWithFloat:1.0]];
			}
			else {
				[m_transform atX:j atY:i put:[NSNumber numberWithFloat:0.0]];
				[m_rotate atX:j atY:i put:[NSNumber numberWithFloat:0.0]];
				[m_sheer atX:j atY:i put:[NSNumber numberWithFloat:0.0]];
				[m_scale atX:j atY:i put:[NSNumber numberWithFloat:0.0]];
				[m_product atX:j atY:i put:[NSNumber numberWithFloat:0.0]];
			}
		}
	}
	
	// Set to centre
	float x_cen, y_cen, z_cen;
	x_cen = [[m_points atX:0 atY:0] floatValue];
	y_cen = [[m_points atX:1 atY:0] floatValue];
	
	// Move centre to 0,0
	[m_transform atX:0 atY:3 put:[NSNumber numberWithFloat:-x_cen]];
	[m_transform atX:1 atY:3 put:[NSNumber numberWithFloat:-y_cen]];
	[m_transform atX:2 atY:3 put:[NSNumber numberWithFloat:-z_cen]];
	m_product = [Matrix newWithMultiply:m_product m2:m_transform];
	
	// Scale to 50% of vertical height
	// Find the maximum point Y and minimum point on Y then get the difference
	float y_min = MAXFLOAT, y_max = -MAXFLOAT, y_scale;
	for (int i = 0; i < [m_points maxY]; i++) {
		for (j = 0; j < [m_product maxX]; j++) {
			if ([[m_points atX:j atY:i] floatValue] > y_max) {
				y_max = [[m_points atX:j atY:i] floatValue];
			}
			else if ([[m_points atX:j atY:i] floatValue] < y_min) {
				y_min = [[m_points atX:j atY:i] floatValue];
			}
		}
	}
	y_scale = 0.5 / ((y_max - y_min) / y_size);
	
	[m_scale atX:0 atY:0 put:[NSNumber numberWithFloat:y_scale]];
	[m_scale atX:1 atY:1 put:[NSNumber numberWithFloat:y_scale]];
	[m_scale atX:2 atY:2 put:[NSNumber numberWithFloat:y_scale]];
	m_product = [Matrix newWithMultiply:m_product m2:m_scale];
	
	
	// Move to centre of the screen
	[m_transform atX:0 atY:3 put:[NSNumber numberWithFloat:x_size / 2]];
	[m_transform atX:1 atY:3 put:[NSNumber numberWithFloat:y_size / 2]];
	[m_transform atX:2 atY:3 put:[NSNumber numberWithFloat:z_cen]];
	m_product = [Matrix newWithMultiply:m_product m2:m_transform];

    [self setNeedsDisplay:YES];
}

- (void)drawRect:(NSRect)rect {
	NSBezierPath * aPath = [NSBezierPath bezierPath];
	m_draw = [Matrix newWithMultiply:m_points m2:m_product];
	int p1, p2;
	float x1, y1, x2, y2;
	
	x_size = rect.size.width;
	y_size = rect.size.height;
	
	[NSBezierPath setDefaultLineWidth:1.0];
	
	for (int i = 0; i < [m_lines maxY]; i++) {
		p1 = [[m_lines atX:0 atY:i] intValue];
		p2 = [[m_lines atX:1 atY:i] intValue];
		
		x1 = [[m_draw atX:0 atY:p1] floatValue];
		y1 = [[m_draw atX:1 atY:p1] floatValue];
		x2 = [[m_draw atX:0 atY:p2] floatValue];
		y2 = [[m_draw atX:1 atY:p2] floatValue];
		
		[aPath moveToPoint:NSMakePoint(x1, y1)];
		[aPath lineToPoint:NSMakePoint(x2, y2)];
	}
	[aPath stroke]; // Draw the result
	
	// Reduce detail while being resized
    if ([self inLiveResize])
    {
        NSRect rects[4];
        int count;
		[NSBezierPath setDefaultFlatness:20.0];
        [self getRectsExposedDuringLiveResize:rects count:&count];
        while (count-- > 0)
        {
            [self setNeedsDisplayInRect:rects[count]];
        }
    }
    else
    {
		[NSBezierPath setDefaultFlatness:0.6];
        [self setNeedsDisplay:YES];
    }
}

- (BOOL)readPoints:(NSString *)fileName {
	float x, y, z;
	int i;
	
	NSString * fileData = [NSString stringWithContentsOfFile: fileName];
	
	if (nil == fileData) {
		return NO;
	}
	
	NSScanner * scanner = [NSScanner scannerWithString:fileData];
	[scanner setCharactersToBeSkipped:[NSCharacterSet characterSetWithCharactersInString:@"\r\n "]];
	NSMutableArray * newPoints = [NSMutableArray array];
	
	while ([scanner scanFloat:&x] && [scanner scanFloat:&y] && [scanner scanFloat:&z]) {
        [newPoints addObject: [NSMutableDictionary dictionaryWithObjectsAndKeys:
							   [NSNumber numberWithFloat:x], @"x",
							   [NSNumber numberWithFloat:y], @"y", 
							   [NSNumber numberWithFloat:z], @"z", 
							   nil]];
    }
	
	// Set the size of the matrix
	m_points = [Matrix newWithXRows:4 YRows:[newPoints count]];
	
	// Fill the new matrix with the vales from the array
	for (i = 0; i < [newPoints count]; i++) {
		[m_points atX:0 atY:i put:[NSNumber numberWithFloat:
								   [[[newPoints objectAtIndex:i] objectForKey:@"x"] floatValue]]];
		[m_points atX:1 atY:i put:[NSNumber numberWithFloat:
								   [[[newPoints objectAtIndex:i] objectForKey:@"y"] floatValue]]];
		[m_points atX:2 atY:i put:[NSNumber numberWithFloat:
								   [[[newPoints objectAtIndex:i] objectForKey:@"z"] floatValue]]];
		[m_points atX:3 atY:i put:[NSNumber numberWithFloat:1.0]];
	}
	
	[newPoints removeAllObjects]; // clear the temporary array
	
	return YES;
}

- (BOOL)readLines:(NSString *)fileName {
	int p1, p2, i;
	
	NSString * fileData = [NSString stringWithContentsOfFile: fileName];
	
	if (nil == fileData) {
		return NO;
	}
	
	NSScanner * scanner = [NSScanner scannerWithString:fileData];
	[scanner setCharactersToBeSkipped:[NSCharacterSet characterSetWithCharactersInString:@"\r\n "]];
	NSMutableArray * newLines = [NSMutableArray array];
	
	while ([scanner scanInt:&p1] && [scanner scanInt:&p2]) {
        [newLines addObject: [NSMutableDictionary dictionaryWithObjectsAndKeys:
							  [NSNumber numberWithInt:p1], @"p1",
							  [NSNumber numberWithInt:p2], @"p2", 
							  nil]];
    }
	
	// Set the size of the matrix
	m_lines = [Matrix newWithXRows:2 YRows:[newLines count]];
	
	// Fill the new matrix with the vales from the array
	for (i = 0; i < [newLines count]; i++) {
		[m_lines atX:0 atY:i put:[NSNumber numberWithFloat:
								  [[[newLines objectAtIndex:i] objectForKey:@"p1"] intValue]]];
		[m_lines atX:1 atY:i put:[NSNumber numberWithFloat:
								  [[[newLines objectAtIndex:i] objectForKey:@"p2"] intValue]]];
	}
	
	[newLines removeAllObjects]; // clear the temporary array
	
	return YES;
}

- (void)dealloc {
	[super dealloc];
}

@end
