use std::thread;

// número de hilos
const NTHREADS: u32 = 2;

// hilo principal
fn main() {
    
    // instancias de nuestros hilos
    let mut children = vec![];
    let x: f32 = 5.0; // VALOR EJEMPLO

    for i in 0..NTHREADS {
        // decide entre el hilo 'a' y el hilo 'b'
        match i {
            0 => children.push(thread::spawn(move || -> f32 {
                let r = 3f32 * x.powf(2f32);
                println!("Hilo {i} = {r}");
                r               
            })),
            1 => children.push(thread::spawn(move || -> f32 {
                let r = (5.0 / x) + 10f32;
                println!("Hilo {i} = {r}");
                r       
            })),
            _ => panic!("Error!"),
        }
    }
    // iteramos por cada hilo y sumamos el resultado de cada hilo.
    // join() asegura que cada hilo haya terminado.
    // unwrap() asegura que no hayamos recibido un error de threading.
    let y = children.into_iter().map(|c| c.join().unwrap()).sum::<f32>();
    println!("y = {y}");
}