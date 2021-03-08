//
//  MainView.swift
//  OriginShopList
//
//  Created by Gabriela Pokropska on 29/09/2020.
//  Copyright © 2020 Gabriela Pokropska. All rights reserved.
//

import SwiftUI
import CoreData

struct MainView: View {
    @Environment(\.managedObjectContext) var moc
    @FetchRequest(entity: Shop.entity(), sortDescriptors: [
        NSSortDescriptor(keyPath: \Shop.listName, ascending: true),
        NSSortDescriptor(keyPath: \Shop.localization, ascending: true)
    ]) var shopLists: FetchedResults<Shop>
    
    @State private var showingAddScreen = false
    @State private var showingLoginScreen = false
    
    var body: some View {
        UINavigationBar.appearance().largeTitleTextAttributes = [.foregroundColor: UIColor(named: "title")!]
        UINavigationBar.appearance().titleTextAttributes = [.foregroundColor: UIColor(named: "title")!]
        return NavigationView {
            List {
                ForEach(shopLists, id:\.self){ shopList in
                    NavigationLink(destination: DetailListView(shop: shopList)){
                        VStack(alignment: .leading){
                            Text(shopList.listName ?? "Unknown name").font(.headline).foregroundColor(Color("text"))
                            Text(shopList.localization ?? "Unknown localization").foregroundColor(Color("text_secondary"))
                        }
                    }
                }.onDelete(perform: deleteList)
            }.navigationBarTitle(Text("Shopping lists"), displayMode: .large)
            .navigationBarItems(leading: Button(action: {
                self.showingLoginScreen.toggle()
            }) {
                Image(systemName: "person.circle").foregroundColor(Color("text"))
            }.sheet(isPresented: $showingAddScreen){
                AddListView().environment(\.managedObjectContext, self.moc)
            }, trailing: Button(action: {
                self.showingAddScreen.toggle()
            }) {
                Image(systemName: "plus").foregroundColor(Color("text"))
            })
        }
    }
    
    func deleteList(at offsets: IndexSet){
        for offset in offsets {
            let list = shopLists[offset]
            
            moc.delete(list)
        }
    }
}

struct MainView_Previews: PreviewProvider {
    static var previews: some View {
        MainView()
    }
}
