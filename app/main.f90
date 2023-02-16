program counter

use, intrinsic :: iso_c_binding, only : C_INT

implicit none

interface
integer(C_INT) function cpu_count() bind(C)
import C_INT
end function
end interface

print '(a,i0)', "Physical CPU count: ", cpu_count()

end program
