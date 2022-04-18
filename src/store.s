.code

StoreKey proc
	
	vlddqu  ymm0, ymmword ptr [rdx]
	vmovdqa ymmword ptr [rcx], ymm0

	ret


StoreKey endp
end