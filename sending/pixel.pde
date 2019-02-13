class Pixel {
  int brightness;
  
  Pixel(){
    
  }

  void seter(int nes) {
    this.brightness = nes;
  }

  String getBrightness() {
    //what we return needs to be a 3 character length
    if (this.brightness < 10) {
      return ("00"+str(this.brightness));
    } else if (this.brightness < 100) {
      return ("0"+str(this.brightness));
    } else {
      return str(this.brightness);
    }
  }
}
