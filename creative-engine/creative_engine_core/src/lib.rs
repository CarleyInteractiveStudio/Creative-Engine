pub mod rendering;
pub mod state;

use egui_winit::winit::{
    event::{Event, WindowEvent},
    event_loop::EventLoop,
    window::Window,
};
use state::State;
use std::sync::Arc;

pub fn run() {
    let event_loop = EventLoop::new().unwrap();
    let window = Arc::new(egui_winit::winit::window::WindowBuilder::new().with_title("Creative Engine").build(&event_loop).unwrap());

    let mut state = pollster::block_on(State::new(window));

    event_loop.run(move |event, event_loop_window_target| {
        match event {
            Event::WindowEvent {
                ref event,
                window_id,
            } if window_id == state.window().id() => { // USE GETTER
                if !state.input(event) {
                    match event {
                        WindowEvent::CloseRequested => event_loop_window_target.exit(),
                        WindowEvent::Resized(physical_size) => {
                            state.resize(*physical_size);
                        }
                        WindowEvent::RedrawRequested => {
                             match state.render() {
                                Ok(_) => {}
                                Err(wgpu::SurfaceError::Lost) => state.resize(state.size()), // USE GETTER
                                Err(wgpu::SurfaceError::OutOfMemory) => event_loop_window_target.exit(),
                                Err(e) => eprintln!("{:?}", e),
                            }
                        }
                        _ => {}
                    }
                }
            }
            Event::AboutToWait => {
                state.window().request_redraw(); // USE GETTER
            }
            _ => {}
        }
    }).unwrap();
}
