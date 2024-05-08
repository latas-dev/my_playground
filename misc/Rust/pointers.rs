// playing with pointers

fn main() {
    let mut my_num = std::u8::MAX;
    unsafe {
        let my_pointer = mut_pointer(&mut my_num);
        print_pointer(my_pointer);
        change_pointer(my_pointer);
        print_pointer(my_pointer);
    }

}

unsafe fn change_pointer(p: *mut u8) {
    *p = 10;
}

unsafe fn print_pointer(p: *const u8) {
    println!("Num: {}\nAddress: {:?}", *p, p);
}

unsafe fn _const_pointer(num: &u8) -> *const u8 {
    num as *const u8
}

unsafe fn mut_pointer(num: &mut u8) -> *mut u8 {
    num as *mut u8
}