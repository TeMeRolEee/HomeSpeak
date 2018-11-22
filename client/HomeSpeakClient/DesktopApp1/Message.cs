
public class Message
{
    public int type { get; set; }
    public string token { get; set; }
    public Data[] data { get; set; }
}

public class Data
{
    public string message { get; set; }
    public int roomID { get; set; }
    public int userID { get; set; }
    public string timestamp { get; set; }
}
