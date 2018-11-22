
public class LoginDataReplay
{
    private static LoginDataReplay instance = null;


    public int type { get; set; }
    public int status { get; set; }
    public ReplayData[] data { get; set; }

    public int getUserID()
    {
        int userID;
        foreach (ReplayData rplData in data)
        {
            foreach (Room rooms in rplData.rooms)
            {
                foreach (User users in rooms.users)
                {
                    if (users.username == LoginData.Instance.username)
                    {
                        userID = users.userID;
                        return userID;
                    }
                }
            }
        }
        return 0;
    }

    public string getUserName(int userId)
    {
        foreach (ReplayData rplData in data)
        {
            foreach (Room rooms in rplData.rooms)
            {
                foreach (User users in rooms.users)
                {
                    if (users.userID == userId)
                    {
                        string username = users.username.ToString();
                        return username;
                    }
                }
            }
        }
        return null;
    }
    public LoginDataReplay()
    {

    }
    public static LoginDataReplay Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new LoginDataReplay();
            }
            return instance;
        }
    }

}

public class ReplayData
{
    public string token { get; set; }
    public Room[] rooms { get; set; }
}

public class Room
{
    public int roomID { get; set; }
    public User[] users { get; set; }
}

public class User
{
    public string username { get; set; }
    public int userID { get; set; }
    
}
