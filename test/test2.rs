fn main(){
    //aaaa zhong wen bian ma you wen ti, yin wei MAXCHAR=128
    
    // let mut z={
    //     let mut t=x*x+x;
    //     t=t+x*y;
    //     t
    // };
    
    // let mut b:i32=a[0];
    // a[0]=1;
    // let mut a=loop {
    //     if b > 0 {
    //         break 3;
    //     }
    //     break 2;
    // };
    
    // let mut t=x*x+x;
    // t=t+x*y;
    // t
    
    // let mut a:[i32;3];
    // a[2*5][1+2]=[1,2,3];
    // *a[2] = 1;
    // let mut b:i32=a[0];
    // a[1]=1;
    // let mut a:[[i32;3];3];
    // a[b[2] + 1][0] = 1;
    
    let a:(i32,[i32;4],[(i32, i32);2]) = (1,[1*5,2,3,4],[(1,2-1),(3,4)]);
    let mut b:i32=a.3[0].1%3;
    a.3[0].1+=*(a);
}
// fn program_6_2__1() {
//     let mut a:i32=1;
//     // let mut b:&mut i32=&mut a;
//     // let b:& i32=&a;
//     let mut c:i32=*b;
//     *b=2;
// }

/*
* ai wo cao zhe zhong wen bian ma zen me zhe me huai a 
ccccccc
*/

// fn main0(mut a:i32, mut b:i32) -> i32 {
    // let mut a1:i32;
    // let mut b1;
    // a1=32;
    // let mut a2:i32=98;
    // let mut b2=14;
    
    // let mut a1:i32 = 1*(2+3)*4<4/2-main0(a-1, b/2)/3;
    
    // if a > 0 {
    //     a = a - 1;
    //     b = b + 1;
    //     main0(a, b);
    // } else if b > 0{
    //     a = a + 1;
    // } else {
    // }
    
    // let mut a1:i32 = 0;
    // while a>0 {
    //     a=a-1;
    //     for mut i in 1..(a+1) / 2 {
    //         a1=i-1;
    //         if (a1 == 0) {
    //             continue;
    //         }
    //     }
    //     break;
    // }
    // return;
// }

fn main1() ->i32{
    loop{
        let mut a = 10;
        break;
    }
    loop{
        let mut a = 10;
        break;
    };
    let mut c = 10;
    let mut b = loop{
        let mut a = 20;
        if(c >= 100){
            break a;
        }
        a = a + 1;
    };
}