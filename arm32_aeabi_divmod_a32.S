/*
 * Calling these functions with two parameters will set R0 and R1
 * then return. This will let GCC pick R0 and R1 for use in soft div.
 */
.global ret_idivmod_values
.global ret_uidivmod_values
ret_idivmod_values:
ret_uidivmod_values:
	bx lr
