//
//  DetailListView.swift
//  OriginShopList
//
//  Created by Gabriela Pokropska on 29/09/2020.
//  Copyright © 2020 Gabriela Pokropska. All rights reserved.
//

import SwiftUI
import CoreData

struct DetailListView: View {
    @Environment(\.managedObjectContext) var moc
    @Environment(\.presentationMode) var presentation
    
    @State private var showingAddScreen = false
    @State private var isCompleted = false
    
    let shop: Shop
    
    var body: some View {
        UINavigationBar.appearance().largeTitleTextAttributes = [.foregroundColor: UIColor(named: "title")!]
        UINavigationBar.appearance().titleTextAttributes = [.foregroundColor: UIColor(named: "title")!]
        
        return NavigationView {
            List {
                ForEach(shop.itemArray, id: \.self) { itemArray in
                    HStack(alignment: .center) {
                        ItemCell(itemArray: itemArray, isCompleted: self.isCompleted)
                    }
                }.onDelete(perform: deleteItem)
            }.navigationBarTitle(Text(self.shop.listName ?? "Products"))
            .navigationBarItems(trailing: Button(action: {
                self.showingAddScreen.toggle()
            }) {
                Image(systemName: "plus").foregroundColor(Color("text"))
            }).sheet(isPresented: $showingAddScreen) {
                AddItemView(shop: self.shop).environment(\.managedObjectContext, self.moc)
            }
        }
        
    }
    
    func deleteItem(at offsets: IndexSet) {
        for offset in offsets {
            let itemArray = shop.itemArray[offset]
            moc.delete(itemArray)
        }
        try? moc.save()
    }
}

struct DetailListView_Previews: PreviewProvider {
    static let moc = NSManagedObjectContext(concurrencyType: .mainQueueConcurrencyType)
    
    static var previews: some View {
        let shop = Shop(context: moc)
        return NavigationView {
            DetailListView(shop: shop)
        }
    }
}

struct ItemCell: View {
    let itemArray: Item
    @State public var isCompleted: Bool
    
    var body: some View {
        HStack {
            ZStack {
                Circle()
                    .stroke(self.isCompleted ? Color("text") : Color("text_secondary"), lineWidth: 1.5)
                    .frame(width: 20, height: 20)
                
                if self.isCompleted {
                    Circle()
                        .fill(Color("text"))
                        .frame(width: 12.5, height: 12.5)
                }
            }
            
            Text(itemArray.name ?? "Unknown name")
                .padding()
                .foregroundColor(self.isCompleted ? Color("text") : Color("text_secondary"))
            }.navigationBarTitle(Text("Products")).foregroundColor(Color("title"))
        .onTapGesture {
            self.isCompleted.toggle()
        }
    }
}
