
public class Message
{
    public int type { get; set; }
    public string token { get; set; }
    public Data[] data { get; set; }
}

public class Data
{
    public string message { get; set; }
    public string roomID { get; set; }
    public string userID { get; set; }
    public long timestamp { get; set; }
}
