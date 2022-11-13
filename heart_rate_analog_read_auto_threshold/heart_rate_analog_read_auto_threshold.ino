void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

int measurements[50];
int highest =0;
int lowest = 0;

void loop() {

  int value = computeValue(measurements, 50);

  float threshold = highest - lowest;
  threshold *= 0.80;
  threshold += lowest;

  if(value > threshold) digitalWrite(13, HIGH);
  else digitalWrite(13,LOW);

  Serial.print(threshold);
  Serial.print(',');
  Serial.print(highest);
   Serial.print(',');
  Serial.print(lowest);
   Serial.print(',');
    Serial.println(value);

}


int computeValue(int* arr, size_t size){

  int newMeasurement = analogRead(A0);

  for(int i=size-1; i>=0; i--){
    arr[i+1] = arr[i];
  }
  arr[0] = newMeasurement;

  highest = newMeasurement;
  lowest = newMeasurement;

  for(int i=0; i<size; i++){
    if(arr[i] > highest) highest = arr[i];
    if(arr[i] < lowest) lowest = arr[i];
  }

  return arr[0];
}