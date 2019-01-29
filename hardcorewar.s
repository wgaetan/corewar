.name "HardCoreWar"
.comment "wassup bitches"

setup:	sti r1,%:setup,%8
		live %101
		sti r1,%:setup,%15
		live %101
		sti r1,%:liveloop,%1
		ld %10,r9
		fork %:continued

liveloop:	live %101
			fork %:liveloop

continued:	ld %1,r2
			ld %20,r5
			sti r1,%:continued,%19
			live %101
			ld %190317061,r4
			ld %13241176,r6
			ld %17105096,r7
			sti r1,%:continued2,%1
continued2: live %101

write:		sti r2,r5,%802
			sti r1,r5,%800
			add r5,r9,r5
l1:			sti r1,%:l1,%8
			live %101
write2:		sti r4,r5,%906
			sti r6,r5,%904
			sti r7,r5,%902
			sti r1,r5,%900
a:			sti r1,%:a,%8
			live %101
			fork %:write

setup2:	sti r1,%:liveloop2,%1
		ld %10,r10
		fork %:continued3

liveloop2:	live %101
			fork %:liveloop2

continued3:	ld %1,r11
			ld %20,r5
			sti r1,%:continued3,%19
			live %101
			ld %190317061,r12
			ld %13241176,r13
			ld %17105096,r14
			sti r1,%:continued4,%1
continued4: live %101
			lfork %4000

write3:		sti r11,r5,%402
			sti r1,r5,%400
			add r5,r10,r5
l2:			sti r1,%:l1,%8
			live %101
write4:		sti r12,r5,%306
			sti r13,r5,%304
			sti r14,r5,%302
			sti r1,r5,%300
b:			sti r1,%:a,%8
			live %101
			fork %:write
