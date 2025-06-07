fn matrix_mult(a: [[i32; 2]; 2], b: [[i32; 2]; 2]) -> [[i32; 2]; 2] {
    let mut result = [[0, 0], [0, 0]];
    for i in 0..2 {
        for j in 0..2 {
            for k in 0..2 {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

fn identity_matrix() -> [[i32; 2]; 2] {
    return [[1, 0], [0, 1]];
}

fn matrix_power(mut base: [[i32; 2]; 2], mut n: i32) -> [[i32; 2]; 2] {
    let mut result = identity_matrix();
    
    while n > 0 {
        if n % 2 == 1 {
            result = matrix_mult(result, base);
        }
        base = matrix_mult(base, base);
        n /= 2;
    }
    return result;
}

fn fast_fibonacci(n: i32) -> i32 {
    if n == 0 {
        return 0;
    }
    
    let m = [[1, 1], [1, 0]];
    let powered = matrix_power(m, n - 1);
    return powered[0][0];
}

fn main() {
    identity_matrix();
    for i in 0..20 {
        let fib = fast_fibonacci(i);
        out fib;  
    }
    
    out fast_fibonacci(30);  // 832040
    out fast_fibonacci(31);  // 1346269
    out fast_fibonacci(32);  // 2178309
    
    let a = [[1, 1], [1, 0]];
    let b = matrix_power(a, 10);
    out b[0][0];  // 89
    out b[0][1];  // 55
    out b[1][0];  // 55
    out b[1][1];  // 34
}


// fn main() {
//     let x = 5;
//     let ref_x = &x;
//     out *ref_x; // 5 
    
//     let mut y = 10;
//     let ref_mut_y = &mut y;
//     *ref_mut_y += 5; 
//     out y; // 15
    
//     let mut z = 20;
//     let ref_z = &mut z;
//     let ref_ref_z = &ref_z;
//     out **ref_ref_z; // 20
//     **ref_ref_z = 25;
//     out z; // 25
    
//     let tuple = (1, 2, 3);
//     out tuple.0; // 1
//     out tuple.1; // 2
//     out tuple.2; // 3
    
//     let mut mut_tuple = (10, 20);
//     mut_tuple.0 += 5;
//     mut_tuple.1 *= 2;
//     out mut_tuple.0; // 15
//     out mut_tuple.1; // 40
    
//     let t = (100, 200);
//     let ref_t = &t;
//     out (*ref_t).0; // 100 
//     out (*ref_t).1; // 200 
    
//     let mut mt = (50, 60);
//     let ref_mut_t = &mut mt;
//     (*ref_mut_t).0 /= 2;
//     (*ref_mut_t).1 -= 10;
//     out mt.0; // 25
//     out mt.1; // 50
    
// }