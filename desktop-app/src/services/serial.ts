import { Serialport } from "tauri-plugin-serialport-api";

const serial: Serialport | undefined = new Serialport({
  path: "COM8",
  baudRate: 460800,
});

serial.open().catch(console.error);

export default {
  sendMessage: (message: object) =>
    serial.write(`${JSON.stringify(message)}\n`),
};
